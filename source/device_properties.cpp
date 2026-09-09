/*
 * Copyright (c) Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <haze.hpp>

namespace haze {

    namespace {

        constinit SetSysSerialNumber g_serial_number = {};
        constinit SetSysFirmwareVersion g_firmware_version = {};
        std::string g_device_description{};

    }

    Result LoadDeviceProperties(const std::string &device_description) {
        /* Initialize set:sys. */
        R_TRY(setsysInitialize());

        /* Ensure we maintain a clean state on exit. */
        ON_SCOPE_EXIT { setsysExit(); };

        /* Get the serial number and firmware version. */
        R_TRY(setsysGetSerialNumber(std::addressof(g_serial_number)));
        R_TRY(setsysGetFirmwareVersion(std::addressof(g_firmware_version)));
        g_device_description = device_description + " HOS: " + g_firmware_version.display_version;

        /* We succeeded. */
        R_SUCCEED();
    }

    const char *GetSerialNumber() {
        return g_serial_number.number;
    }

    const char *GetFirmwareVersion() {
        return g_firmware_version.display_version;
    }

    const char *GetDeviceDescription() {
        return g_device_description.c_str();
    }
}
