using System;
using System.Runtime.InteropServices;
using System.Text;

public static class Imports
{
    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool CheckRemoteDebuggerPresent(
        IntPtr hProcess,
        ref bool isDebuggerPresent);

    [DllImport("user32.dll", SetLastError = true)]
    public static extern int GetWindowText(
        IntPtr hWnd,
        StringBuilder lpString,
        int nMaxCount);

    [DllImport("user32.dll", SetLastError = true)]
    public static extern int GetWindowTextLength(IntPtr hWnd);

    [DllImport("user32.dll")]
    [return: MarshalAs(UnmanagedType.Bool)]
    public static extern bool IsWindowVisible(IntPtr hWnd);
}

//tnx to bxdev <3