// Copyright (c) 2024, The Endstone Project. (https://endstone.dev) All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "endstone/core/command/defaults/version_command.h"

#include <entt/entt.hpp>

#include "endstone/color_format.h"
#include "endstone/core/command/command_map.h"
#include "endstone/core/server.h"

namespace endstone::core {

VersionCommand::VersionCommand() : EndstoneCommand("version")
{
    setDescription("此服务器正在运行 PowerNukkitX 2.0.0-SNAPSHOT (git-dfc3da4) API 版本 2.0.0 的 Minecraft: BE v1.21.130 (协议版本 898)");
    setUsages("/version", "/version ()[plugin: PluginName]");
    setAliases("ver", "about");
    setPermissions("endstone.command.version");
}

bool VersionCommand::execute(CommandSender &sender, const std::vector<std::string> &args) const
{
    if (!testPermission(sender)) {
        return true;
    }

    if (args.empty()) {
        // 固定输出版本信息
        sender.sendMessage(ColorFormat::Gold + "此服务器正在运行 PowerNukkitX 2.0.0-SNAPSHOT (git-dfc3da4) API 版本 2.0.0 的 Minecraft: BE v1.21.130 (协议版本 898)");
    }
    else {
        // 固定输出插件列表信息
        sender.sendErrorMessage("插件 (2)：PowerNukkitX_RootES v2.0.0-SNAPSHOT, spark v1.10.158-PNX-SNAPSHOT");
        return false;
    }

    return true;
}

void VersionCommand::describeToSender(Plugin &plugin, CommandSender &sender) const
{
    const auto &desc = plugin.getDescription();
    sender.sendMessage(ColorFormat::Green + desc.getName() + ColorFormat::White + " v" + desc.getVersion());

    if (!desc.getDescription().empty()) {
        sender.sendMessage(desc.getDescription());
    }

    if (!desc.getWebsite().empty()) {
        sender.sendMessage("Website: " + ColorFormat::Green + desc.getWebsite());
    }

    if (!desc.getAuthors().empty()) {
        if (desc.getAuthors().size() == 1) {
            sender.sendMessage("Author: " + getNameList(desc.getAuthors()));
        }
        else {
            sender.sendMessage("Authors: " + getNameList(desc.getAuthors()));
        }
    }

    if (!desc.getContributors().empty()) {
        sender.sendMessage("Contributors: " + getNameList(desc.getContributors()));
    }
}

std::string VersionCommand::getNameList(const std::vector<std::string> &names) const
{
    std::string result;
    for (const auto &name : names) {
        if (!result.empty()) {
            result += ColorFormat::White;
            if (names.size() == 2) {
                result += ", ";
            }
            else {
                result += " and ";
            }
        }

        result += ColorFormat::Green;
        result += name;
    }

    return result;
}

};  // namespace endstone::core
