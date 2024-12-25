#pragma once

#include "../Module.hpp"
#include "../../../../SDK/Client/Network/Packet/SetTitlePacket.hpp"
#include "../Misc/HiveModeCatcher/HiveModeCatcherListener.hpp"


class AutoRQ : public Module {
private:
    bool triggered = false;
    std::string teamcolor= "THIS IS NEEDED TRUST!!!!!!!!!!!!!!";
    std::string Copy_CS = "THIS IS NEEDED EVEN MORE TRUST!!!!";
public:
    AutoRQ() : Module("Hive Utils", "Handy utilities for The Hive partnered server",
                      IDR_AUTORQ_PNG, "") { //maybe we need a new icon??? let @treegfx cook
        Module::setup();
    };

    void onEnable() override {
        Listen(this, PacketEvent, &AutoRQ::onPacketReceive)
        Module::onEnable();
    }

    void onDisable() override {
        Deafen(this, PacketEvent, &AutoRQ::onPacketReceive)
        Module::onDisable();
    }

    void defaultConfig() override {
        if (settings.getSettingByName<std::string>("command") == nullptr)
            settings.addSetting("command", (std::string)"");
        if (settings.getSettingByName<bool>("ReQ") == nullptr)
            settings.addSetting("ReQ", true);
        if (settings.getSettingByName<bool>("solo") == nullptr)
            settings.addSetting("solo", false);
        if (settings.getSettingByName<bool>("eliminated") == nullptr)
            settings.addSetting("eliminated", true);
        if (settings.getSettingByName<bool>("hub") == nullptr)
            settings.addSetting("hub", false);
        if (settings.getSettingByName<bool>("murderer") == nullptr)
            settings.addSetting("murderer", false);
        if (settings.getSettingByName<bool>("sheriff") == nullptr)
            settings.addSetting("sheriff", false);
        if (settings.getSettingByName<bool>("innocent") == nullptr)
            settings.addSetting("innocent", false);
        if (settings.getSettingByName<bool>("hider") == nullptr)
            settings.addSetting("hider", false);
        if (settings.getSettingByName<bool>("seeker") == nullptr)
            settings.addSetting("seeker", false);
        if (settings.getSettingByName<bool>("death") == nullptr)
            settings.addSetting("death", false);
        if (settings.getSettingByName<bool>("runner") == nullptr)
            settings.addSetting("runner", false);
        if (settings.getSettingByName<bool>("AutoMapAvoider") == nullptr)
            settings.addSetting("AutoMapAvoider", false);
        if (settings.getSettingByName<std::string>("text") == nullptr)
            settings.addSetting("text", (std::string) "Input maps, like this");
        if (settings.getSettingByName<bool>("promomessage") == nullptr)
            settings.addSetting("promomessage", true);
        if (settings.getSettingByName<bool>("replace") == nullptr)
            settings.addSetting("replace", true);
        if (settings.getSettingByName<bool>("copyCS") == nullptr)
            settings.addSetting("copyCS", false);
        if (settings.getSettingByName<bool>("includecommand") == nullptr)
            settings.addSetting("includecommand", true);
    }

    void settingsRender(float settingsOffset) override {
        float x = Constraints::PercentageConstraint(0.019, "left");
        float y = Constraints::PercentageConstraint(0.10, "top");

        const float scrollviewWidth = Constraints::RelativeConstraint(0.5, "height", true);


        FlarialGUI::ScrollBar(x, y, 140, Constraints::SpacingConstraint(5.5, scrollviewWidth), 2);
        FlarialGUI::SetScrollView(x - settingsOffset, Constraints::PercentageConstraint(0.00, "top"),
                                  Constraints::RelativeConstraint(1.0, "width"),
                                  Constraints::RelativeConstraint(0.88f, "height"));
        this->addHeader("General");
        this->addToggle("Use /hub instead of /q", "", this->settings.getSettingByName<bool>("hub")->value);

        this->addHeader("Auto Re Q");
        this->addToggle("Auto re-queue ", "Find a new game when the current game is over", this->settings.getSettingByName<bool>("ReQ")->value);
        this->addToggle("Solo mode ", "Re-Q when you finish or die in a game. pls dont use while in a party", this->settings.getSettingByName<bool>("solo")->value);
        this->addToggle("Re-Q on Team elimenation", "Re-Q when your team has been ELIMINATED", this->settings.getSettingByName<bool>("eliminated")->value);

        this->addHeader("Role Avoider");

        this->addHeader("Murder Mystery");
        this->addToggle("Murder", "re q when you get murder", this->settings.getSettingByName<bool>("murderer")->value);
        this->addToggle("Sheriff", "re q when you get sheriff", this->settings.getSettingByName<bool>("sheriff")->value);
        this->addToggle("Innocent", "re q when you get innocent", this->settings.getSettingByName<bool>("innocent")->value);

        this->addHeader("Hide and Seek");
        this->addToggle("Hider", "re q when you get hider", this->settings.getSettingByName<bool>("hider")->value);
        this->addToggle("Seeker", "re q when you get seeker", this->settings.getSettingByName<bool>("seeker")->value);

        this->addHeader("Deathrun");
        this->addToggle("Death", "re q when you get death", this->settings.getSettingByName<bool>("death")->value);
        this->addToggle("Runner", "re q when you get runner", this->settings.getSettingByName<bool>("runner")->value);

        this->addHeader("Map avoider");

        this->addToggle("Avoid", "", this->settings.getSettingByName<bool>("AutoMapAvoider")->value);
        this->addTextBox("Maps", "Avoid Maps (Hive). Input one or more maps using comma's.", settings.getSettingByName<std::string>("text")->value);

        this->addHeader("Copy Custom Server code");
        this->addToggle("Copy CS code Keybind", "When setting, hold the new bind for 2 seconds", this->settings.getSettingByName<bool>("copyCS")->value);
        this->addToggle("Include command", "Include /cs", this->settings.getSettingByName<bool>("includecommand")->value);

        this->addHeader("Debloat chat");
        this->addToggle("Promo message", "Removes all promo/info messages starting with [!]", this->settings.getSettingByName<bool>("promomessage")->value);

        FlarialGUI::UnsetScrollView();
        this->resetPadding();
    }


    inline void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
    }


    void onPacketReceive(PacketEvent &event) {
        MinecraftPacketIds id = event.getPacket()->getId();

        if (id == MinecraftPacketIds::SetTitle) {
            auto *pkt = reinterpret_cast<SetTitlePacket *>(event.getPacket());
            if (this->settings.getSettingByName<bool>("ReQ")->value) {
                if (this->settings.getSettingByName<bool>("solo")->value) {


                    if (//pkt->text == "§cYou're a spectator!" || //this brobably isn't needed anymore
                        pkt->text == "§cYou died!" ||
                        pkt->text == "§7You're spectating the §as§eh§6o§cw§7!") {
                        reQ();

                    }
                }
            }
            if (this->settings.getSettingByName<bool>("copyCS")->value)
            {
                if (!pkt->text.empty() && pkt->text.find(Copy_CS) == std::string::npos){
                    if (pkt->text.length() >= 15 && pkt->text.substr(0, 13) == "§eJoin Code:") {
                        Copy_CS = pkt->text;
                        if (!this->settings.getSettingByName<bool>("includecommand")->value) {
                            ImGui::SetClipboardText(pkt->text.substr(17, pkt->text.length()).c_str());
                        }
                        else{
                            ImGui::SetClipboardText(("/cs " + pkt->text.substr(17, pkt->text.length())).c_str());
                        }
                        FlarialGUI::Notify("Compied CS Code to Clipboard");
                    }
                }
            }
        }
        if (id == MinecraftPacketIds::Text) {
            auto *pkt = reinterpret_cast<TextPacket *>(event.getPacket());
            if (this->settings.getSettingByName<bool>("ReQ")->value) {
                //if(!module->settings.getSettingByName<bool>("solo")->value) {
                if (pkt->message == "§c§l» §r§c§lGame OVER!") {
                    reQ();
                    return;
                }
                if (this->settings.getSettingByName<bool>("eliminated")->value){
                    if (pkt->message.length() > 27){
                        if (pkt->message.substr(12, 15) == "You are on the "){
                            teamcolor = pkt->message.substr(27, pkt->message.length() - 28);

                            FlarialGUI::Notify("You are on the: " + teamcolor);
                        }
                    }

                    if (pkt->message.find("§7has been §cELIMINATED§7!") != std::string::npos && pkt->message.find(teamcolor) != std::string::npos && !teamcolor.empty()){
                        reQ();
                        FlarialGUI::Notify("Your Team has been ELIMINATED");
                        return;
                    }
                }
                if (this->settings.getSettingByName<bool>("solo")->value) {

                    if (pkt->message.substr(0,48) == "§a§l» §r§eYou finished all maps and came in" || //gravity
                        pkt->message.substr(0,30) == "§a§l» §r§eYou finished in") { //deathrun
                        reQ();

                    }
                }
            }
            if (this->settings.getSettingByName<bool>("murderer")->value) {

                if (pkt->message == "§c§l» §r§c§lMurderer") {
                    reQ();
                    FlarialGUI::Notify("Found role Murderer");

                }
            }
            if (this->settings.getSettingByName<bool>("sheriff")->value) {

                if (pkt->message == "§9§l» §r§9§lSheriff") {
                    reQ();
                    FlarialGUI::Notify("Found role Sheriff");

                }
            }
            if (this->settings.getSettingByName<bool>("innocent")->value) {

                if (pkt->message == "§a§l» §r§a§lInnocent") {
                    reQ();
                    FlarialGUI::Notify("Found role Innocent");

                }
            }
            if (this->settings.getSettingByName<bool>("death")->value) {

                if (pkt->message == "§d§l» §r§bYou are a §cDeath") {
                    reQ();
                    FlarialGUI::Notify("Found role Death");

                }
            }
            if (this->settings.getSettingByName<bool>("runner")->value) {

                if (pkt->message == "§d§l» §r§bYou are a §aRunner") {
                    reQ();
                    FlarialGUI::Notify("Found role Runner");

                }
            }
            if (this->settings.getSettingByName<bool>("hider")->value) {

                if (pkt->message == "§e§l» §rYou are a §eHIDER") {
                    reQ();
                    FlarialGUI::Notify("Found role Hider");

                }
            }
            if (this->settings.getSettingByName<bool>("seeker")->value) {

                if (pkt->message == "§c§l» §rYou are a §cSEEKER") {
                    reQ();
                    FlarialGUI::Notify("Found role Seeker");

                }
            }
            if (this->settings.getSettingByName<bool>("AutoMapAvoider")->value) {
                std::string maps_to_avoid = this->settings.getSettingByName<std::string>("text")->value;
                std::stringstream ss(maps_to_avoid);
                std::string fixed_value = "§b§l» §r§e";
                std::vector<int> vect;
                std::vector<std::string> result;
                if (pkt->message.substr(0, 15) == fixed_value) {
                    while (ss.good()) {
                        std::string substr;
                        getline(ss, substr, ',');
                        ltrim(substr);
                        result.push_back(substr);
                    }

                    for (std::size_t i = 0; i < result.size(); i++) {
                        std::string evaluate_string = fixed_value + result[i];
                        std::transform(evaluate_string.begin(), evaluate_string.end(), evaluate_string.begin(),
                                       ::tolower);
                        std::transform(pkt->message.begin(), pkt->message.end(), pkt->message.begin(), ::tolower);
                        if (pkt->message.substr(0, (evaluate_string.length())) == evaluate_string) {
                            reQ();
                            FlarialGUI::Notify("Found map: " + result[i]);
                        }
                    }
                }
            }

            if (this->settings.getSettingByName<bool>("promomessage")->value) {
                if (pkt->message.find("§6[§e!§6]")!= std::string::npos){
                    event.cancel();
                }
            }
        }
    }

    void reQ() {
        if (!this->settings.getSettingByName<bool>("hub")->value) {
            FlarialGUI::Notify("Finding a new game of " + HiveModeCatcherListener::fullgamemodename);

            std::shared_ptr<Packet> packet = SDK::createPacket(77);
            auto *command_packet = reinterpret_cast<CommandRequestPacket *>(packet.get());
            command_packet->command = "/q " + HiveModeCatcherListener::currentGame;

            command_packet->origin.type = CommandOriginType::Player;

            command_packet->InternalSource = true;
            SDK::clientInstance->getPacketSender()->sendToServer(command_packet);
        } else {
            FlarialGUI::Notify("Executing command /hub");
            std::shared_ptr<Packet> packet = SDK::createPacket(77);
            auto *command_packet = reinterpret_cast<CommandRequestPacket *>(packet.get());

            command_packet->command = "/hub";

            command_packet->origin.type = CommandOriginType::Player;

            command_packet->InternalSource = true;

            SDK::clientInstance->getPacketSender()->sendToServer(command_packet);
        }
    }
};

