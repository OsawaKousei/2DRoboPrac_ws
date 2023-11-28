// Copyright 2016 Open Source Robotics Foundation, Inc.
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

#ifndef KEY_EVENT_NODES__VISIBILITY_H_
#define KEY_EVENT_NODES__VISIBILITY_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__

  #ifdef __GNUC__
    #define KEY_EVENT_NODES_EXPORT __attribute__ ((dllexport))
    #define KEY_EVENT_NODES_IMPORT __attribute__ ((dllimport))
  #else
    #define KEY_EVENT_NODES_EXPORT __declspec(dllexport)
    #define KEY_EVENT_NODES_IMPORT __declspec(dllimport)
  #endif

  #ifdef KEY_EVENT_NODES_DLL
    #define KEY_EVENT_NODES_PUBLIC KEY_EVENT_NODES_EXPORT
  #else
    #define KEY_EVENT_NODES_PUBLIC KEY_EVENT_NODES_IMPORT
  #endif

  #define KEY_EVENT_NODES_PUBLIC_TYPE KEY_EVENT_NODES_PUBLIC

  #define KEY_EVENT_NODES_LOCAL

#else

  #define KEY_EVENT_NODES_EXPORT __attribute__ ((visibility("default")))
  #define KEY_EVENT_NODES_IMPORT

  #if __GNUC__ >= 4
    #define KEY_EVENT_NODES_PUBLIC __attribute__ ((visibility("default")))
    #define KEY_EVENT_NODES_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define KEY_EVENT_NODES_PUBLIC
    #define KEY_EVENT_NODES_LOCAL
  #endif

  #define KEY_EVENT_NODES_PUBLIC_TYPE
#endif

#ifdef __cplusplus
}
#endif

#endif  // KEY_EVENT_NODES__VISIBILITY_H_
