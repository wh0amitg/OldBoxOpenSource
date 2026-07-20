using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;

static class Detections
{
    public const string GameProcessName = "GoreBox";

    private static readonly HashSet<string> SuspiciousWindowTitles = new HashSet<string>(StringComparer.OrdinalIgnoreCase)
    {
        "Cheat Engine", "Process Hacker", "System Informer", "x64dbg", "x32dbg", "IDA Pro", "OllyDbg",
        "BepInEx", "MelonLoader"
    };

    private static readonly HashSet<string> ModFolderNames = new HashSet<string>(StringComparer.OrdinalIgnoreCase)
    {
        "BepInEx", "MelonLoader", "Mods", "UserMods", "UserLibs", "dotnet", "Plugins"
    };

    private static readonly HashSet<string> ForbiddenFiles = new HashSet<string>(StringComparer.OrdinalIgnoreCase)
    {
        "winhttp.dll", "winmm.dll", "dinput8.dll", "dxgi.dll", "d3d9.dll", "d3d11.dll", "d3d12.dll",
        "opengl32.dll", "xinput1_3.dll", "xinput1_4.dll", "xinput9_1_0.dll", "dsound.dll", "ddraw.dll",
        "msacm32.dll", "cryptsp.dll", "doorstop_config.ini", "doorstop_config.xml", "doorstop_config",
        "doorstop.dll", "BepInEx.cfg", "MelonLoader.dll", "bootstrap.dll", "IPA.Injector.exe",
        "IPA.Loader.dll", "BSIPA.dll", "UnityModManager.dll", "UnityModManagerConfig.xml", "injector.dll",
        "loader.dll", "proxy.dll", "hack.dll", "modloader.dll", "mod_loader.dll", "imgui.ini",
        "imgui.dll", "cimgui.dll", "REFramework.dll", "0Harmony.dll", "HarmonyX.dll", "MonoMod.RuntimeDetour.dll",
        "Mono.Cecil.dll", "GameAssembly.dll.bak", "global-metadata.dat.bak", "Il2CppInterop.Runtime.dll",
        "UnhollowerBaseLib.dll", "speedhack.dll"
    };

    private static bool CheckDirectoryForMods(string path)
    {
        if (string.IsNullOrEmpty(path) || !Directory.Exists(path)) return false;

        try
        {
            foreach (var dir in Directory.GetDirectories(path))
            {
                if (ModFolderNames.Contains(Path.GetFileName(dir)))
                    return true;
            }

            foreach (var file in Directory.GetFiles(path))
            {
                if (ForbiddenFiles.Contains(Path.GetFileName(file)))
                    return true;
            }
        }
        catch { }
        return false;
    }

    public static bool IntegrityCheckFailed()
    {
        string localDir = AppContext.BaseDirectory;
        if (CheckDirectoryForMods(localDir)) return true;

        try
        {
            DirectoryInfo parent = Directory.GetParent(localDir);
            if (parent != null) parent = Directory.GetParent(parent.FullName);
            if (parent != null) parent = Directory.GetParent(parent.FullName);

            if (parent != null && CheckDirectoryForMods(parent.FullName))
            {
                return true;
            }
        }
        catch { }

        return false;
    }

    public static bool IsGameBeingDebugged()
    {
        var targets = Process.GetProcessesByName(GameProcessName);
        if (targets.Length == 0) return false;

        foreach (var proc in targets)
        {
            try
            {
                bool isTargetDebugged = false;
                if (Imports.CheckRemoteDebuggerPresent(proc.Handle, ref isTargetDebugged) && isTargetDebugged)
                {
                    return true;
                }
            }
            catch { return true; }
        }
        return false;
    }

    public static bool ScanBadWindows()
    {
        foreach (var proc in Process.GetProcesses())
        {
            try
            {
                IntPtr hWnd = proc.MainWindowHandle;
                if (hWnd == IntPtr.Zero || !Imports.IsWindowVisible(hWnd))
                    continue;

                int length = Imports.GetWindowTextLength(hWnd);
                if (length == 0) continue;

                StringBuilder builder = new StringBuilder(length + 1);
                Imports.GetWindowText(hWnd, builder, builder.Capacity);
                string title = builder.ToString();

                if (SuspiciousWindowTitles.Any(badTitle => title.IndexOf(badTitle, StringComparison.OrdinalIgnoreCase) >= 0))
                {
                    return true;
                }
            }
            catch { }
        }
        return false;
    }

    public static void KillGame()
    {
        foreach (var proc in Process.GetProcessesByName(GameProcessName))
        {
            try { proc.Kill(); } catch { }
        }
    }
}

public static class Entry
{
    public static void Main()
    {
        Thread.Sleep(2000);

        while (true)
        {
            var games = Process.GetProcessesByName(Detections.GameProcessName);

            if (games.Length == 0)
            {
                Thread.Sleep(3000);
                if (Process.GetProcessesByName(Detections.GameProcessName).Length == 0)
                    break;
            }
            if (Detections.IntegrityCheckFailed() || Detections.IsGameBeingDebugged() || Detections.ScanBadWindows())
            {
                Detections.KillGame();
                Thread.Sleep(1000);
                Environment.Exit(0);
            }

            Thread.Sleep(1000);
        }
    }
}

//tnx to bxdev <3