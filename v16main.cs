// v16 multiplayer
using BepInEx;
using BepInEx.Unity.IL2CPP;
using HarmonyLib;
using Photon.Pun;
using PlayFab;
using PlayFab.ClientModels;
using UnityEngine.Networking;

namespace GoreBoxMain
{
    [BepInPlugin("GoreBox", "GoreBoxMain", "1.0")]
    public class GoreBoxClass : BasePlugin
    {
        public override void Load()
        {
            Harmony harmony = new Harmony("GoreBox");
            harmony.PatchAll();
        }

        #region Multiplayer Patch
        [HarmonyPatch(typeof(VersionValidator), "YOUR_METHOD_NAME_HERE")]
        public static class VersionValPatch
        {
            private static bool Prefix(VersionValidator __instance)
            {
                PhotonNetwork.PhotonServerSettings.AppSettings.AppIdRealtime = "YOUR_PHOTON_APP_ID";
                PhotonNetwork.PhotonServerSettings.AppSettings.AppIdVoice = "YOUR_PHOTON_VOICE_ID";
                PlayFabSettings.PlayFabSharedPrivate.TitleId = "YOUR_TITLE_ID";
                PlayFabSettings.PlayFabSharedPrivate.ProductionEnvironmentUrl = "https://YOUR_TITLE_ID.playfabapi.com";

                LoginWithCustomIDRequest loginRequest = new LoginWithCustomIDRequest
                {
                    CreateAccount = new Il2CppSystem.Nullable<bool>(true),
                    CustomId = UnityEngine.SystemInfo.deviceUniqueIdentifier
                };

                System.Action<LoginResult> onSuccess = delegate (LoginResult result)
                {
                    __instance.LoginResult(result); // Find correct LoginResult in dnSpy
                };

                System.Action<PlayFabError> onError = delegate (PlayFabError err)
                {
                    __instance.PlayFabError(err); // Find correct PlayFabError in dnSpy
                };

                PlayFabClientAPI.LoginWithCustomID(loginRequest, onSuccess, onError, null, null);

                return false;
            }
        }

        public class Bypass
        {
            [HarmonyPatch(typeof(ITGTCKR.HCCBOMCIBMC), "MoveNext")] //find class in ITGTCKR that have "MoveNext"
            public static class ITGTCKRBypass
            {
                public static bool Prefix(ref bool __result)
                {
                    __result = false;
                    return false;
                }
            }

            [HarmonyPatch(typeof(ConnectionMaster.AGFGNFNFHLF), "MoveNext")] //find class in ConnectionMaster that have "MoveNext"
            public static class ConnectionMasterBypass
            {
                public static bool Prefix(ref bool __result)
                {
                    __result = false;
                    return false;
                }
            }
        }


        [HarmonyPatch(typeof(VersionValidator.CPJDDEHIFKG), "FGFPPHBOGCN")]
        public static class VersionValidatorPatch1
        {
            public static void Prefix(VersionValidator.CPJDDEHIFKG __instance, GetAccountInfoResult result)
            {
                result.AccountInfo.SteamInfo = new UserSteamInfo();
            }
        }
    }
}

// memphis we love u <3
