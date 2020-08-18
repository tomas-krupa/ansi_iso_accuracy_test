/**
 * @file AnsiIsoNativeInterface.h
 *
 * @copyright Copyright (c) 2020 Innovatrics s.r.o. All rights reserved.
 *
 * @maintainer Tomas Krupa <tomas.krupa@innovatrics.com>
 * @created 10.08.2020
 *
 */

#pragma once

#include <iengine_ansi_iso.h>

/**
 * @brief AnsiIsoNativeInterface
 *
 * Implements real interface to AnsiIso native library.
 */
class AnsiIsoNativeInterface
{
public:
  int IEngine_Init() const { ::IEngine_Init(); }

  int IEngine_Terminate() const { ::IEngine_Terminate(); }

  const char* IEngine_GetVersionString() const { ::IEngine_GetVersionString(); }

  int IEngine_GetHwidByMethod(IENGINE_HWID_METHOD method,
                              char* hwid,
                              int* length) const
  {
    ::IEngine_GetHwidByMethod(method, hwid, length);
  }
};
