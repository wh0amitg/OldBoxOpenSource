using DiscordRPC; // https://github.com/Lachee/discord-rpc-csharp/releases

public static DiscordRpcClient client;

// add into "public override void Load()" line "InitDiscord();"
public static void InitDiscord()
{
    try
    {
        client = new DiscordRpcClient(""); // your client id on discord developer portal (https://discord.com/developers/applications) 

        client.Initialize();

        client.SetPresence(new RichPresence()
        {
            Details = "",
            State = "",
            Assets = new Assets()
            {
                LargeImageKey = "logo",
                LargeImageText = "logo"
            }
        });
    }
    catch { }
}

public static void UpdateStatus(string state)
{
    if (client != null && client.IsInitialized)
    {
        client.UpdateState(state);
    }
}

// working only on v15
// and add into plugins Newtonsoft.Json.dll + DiscordRPC.dll for stable working