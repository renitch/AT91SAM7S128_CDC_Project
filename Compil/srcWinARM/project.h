//-----------------------------------------------------------------------------
//           ATMEL Microcontroller Software Support  -  ROUSSET  -
//-----------------------------------------------------------------------------
// DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
// DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
// OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------
//  File Name           : project.h
//  Object              : project specific include file to AT91SAM7S256
//  Creation            : JPP   09-May-2006
//-----------------------------------------------------------------------------

// modified by Martin Thomas :
// - support for different models
// - __inline --> static inline

#ifndef _PROJECT_H
#define _PROJECT_H

/// Include your AT91 Library files and specific compiler definitions

#include "AT91SAM7S-EK.h"

#define __inline static inline

#if defined(__WINARMSUBMDL_AT91SAM7S64__)
#include "AT91SAM7S64.h"
#include "lib_AT91SAM7S64.h"
#elif defined(__WINARMSUBMDL_AT91SAM7S256__)
#include "AT91SAM7S256.h"
#include "lib_AT91SAM7S256.h"
#else
#error "Submodel undefined"
#endif

#endif  // _PROJECT_H
