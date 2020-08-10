//
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//
// try_catch_helpers.h: Helper macros for all SPXAPI methods; use these in each public API function to
//                      ensure no C++ exceptions leak out of our C API implementation
//

#pragma once

#include <speechapi_c_common.h>
#include <exception.h>

#if defined(__GNUG__) && defined(__linux__) && !defined(ANDROID) && !defined(__ANDROID__)
#include <cxxabi.h>
#define SHOULD_HANDLE_FORCED_UNWIND 1

#define SPXAPI_FORCED_UNWIND_CATCH                          \
    catch (abi::__forced_unwind&)                           \
    {                                                       \
        SPX_REPORT_ON_FAIL(SPXERR_ABORT);                   \
        throw;                                              \
    }

#else
#define SPXAPI_FORCED_UNWIND_CATCH
#endif

using Microsoft::CognitiveServices::Speech::Impl::StoreException;

#define SPXAPI_INIT_HR_TRY(hr)                              \
{                                                           \
    SPX_INIT_HR(hr);                                        \
    try

#define SPXAPI_TRY()                                        \
{                                                           \
    try

#define SPXAPI_CATCH(x)                                     \
    catch (SPXHR hrx)                                       \
    {                                                       \
        SPX_REPORT_ON_FAIL(hrx);                            \
        x = hrx;                                            \
    }                                                       \
    catch (ExceptionWithCallStack& ex)                      \
    {                                                       \
       x = StoreException(std::move(ex));                   \
    }                                                       \
    catch (const std::exception& ex)                        \
    {                                                       \
       x = StoreException(ex);                              \
    }                                                       \
    SPXAPI_FORCED_UNWIND_CATCH                              \
    catch (...)                                             \
    {                                                       \
        SPX_REPORT_ON_FAIL(SPXERR_UNHANDLED_EXCEPTION);     \
        x = SPXERR_UNHANDLED_EXCEPTION;                     \
    }

#define SPXAPI_CATCH_ONLY()                                 \
    catch (SPXHR hrx)                                       \
    {                                                       \
        SPX_REPORT_ON_FAIL(hrx);                            \
        error = stringify(hrx);                             \
    }                                                       \
    catch (const ExceptionWithCallStack& ex)                \
    {                                                       \
       SPX_REPORT_ON_FAIL(ex.GetErrorCode());               \
       error = stringify(ex.GetErrorCode());                \
       error += " ";                                        \
       error += ex.GetCallStack();                          \
       SPX_TRACE_ERROR("ExceptionWithCallStack: %s", error.c_str());   \
    }                                                       \
    catch (const std::exception& e)                         \
    {                                                       \
        error = e.what();                                   \
        SPX_TRACE_ERROR("Exception: %s", error.c_str());    \
    }                                                       \
    SPXAPI_FORCED_UNWIND_CATCH                              \
    catch (...)                                             \
    {                                                       \
        SPX_TRACE_ERROR("UNHANDLED Exception.");            \
        SPX_REPORT_ON_FAIL(SPXERR_UNHANDLED_EXCEPTION);     \
        error = "SPXERR_UNHANDLED_EXCEPTION";               \
    }                                                       \
}                                                           \

// Use in destructors where throwing (and re-throwing) is undefined.
#define SPXAPI_CATCH_ONLY_NO_FORCED_UNWIND()                \
    catch (SPXHR hrx)                                       \
    {                                                       \
        SPX_REPORT_ON_FAIL(hrx);                            \
        error = stringify(hrx);                             \
    }                                                       \
    catch (const ExceptionWithCallStack& ex)                \
    {                                                       \
       SPX_REPORT_ON_FAIL(ex.GetErrorCode());               \
       error = stringify(ex.GetErrorCode());                \
       error += " ";                                        \
       error += ex.GetCallStack();                          \
       SPX_TRACE_ERROR("ExceptionWithCallStack: %s", error.c_str());    \
    }                                                       \
    catch (const std::exception& e)                         \
    {                                                       \
        error = e.what();                                   \
        SPX_TRACE_ERROR("Exception: %s", error.c_str());    \
    }                                                       \
    catch (...)                                             \
    {                                                       \
        SPX_TRACE_ERROR("UNHANDLED Exception.");            \
        SPX_REPORT_ON_FAIL(SPXERR_UNHANDLED_EXCEPTION);     \
        error = "SPXERR_UNHANDLED_EXCEPTION";               \
    }                                                       \
}                                                           \

#define SPXAPI_CATCH_AND_RETURN_HR(hr)                      \
    SPXAPI_CATCH(hr);                                       \
    SPX_RETURN_HR(hr);                                      \
}

#define SPXAPI_CATCH_AND_RETURN_HR_EXCLUDE(hr, excludeHr)   \
    SPXAPI_CATCH(hr);                                       \
    do {                                                    \
        SPXHR x = hr;                                       \
        if (SPX_FAILED(x) && (x != (excludeHr))) {          \
            __SPX_TRACE_HR("SPX_RETURN_ON_FAIL: ", hr, x);  \
        }                                                   \
        return x;                                           \
    } while (0);                                            \
}

#define SPXAPI_CATCH_AND_RETURN(hr, x)                      \
    SPXAPI_CATCH(hr);                                       \
    return x;                                               \
}
