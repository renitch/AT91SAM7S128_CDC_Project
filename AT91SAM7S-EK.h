// ----------------------------------------------------------------------------
//         ATMEL Microcontroller Software Support  -  ROUSSET  -
// ----------------------------------------------------------------------------
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
// ----------------------------------------------------------------------------
// File Name           : AT91SAM7S-EK.h
// Object              : AT91SAM7S-EK Evaluation Board Features Definition File
// Creation            : JPP 21-Jun-2006
//  ----------------------------------------------------------------------------

#ifndef AT91SAM7S_EK_H
#define AT91SAM7S_EK_H

/*-----------------*/
/* LEDs Definition */
/*-----------------*/
/*                                     PIO   Flash    PA    PB   PIN */
#define AT91B_LED1          (1<<18)	/* PA18 / PGMEN0 & PWM0 TIOA0  48 */
#define AT91B_LED2          (1<<17)	/* PA17 / PGMEN1 & PWM1 TIOB0  47 */
#define AT91B_NB_LEB        2
#define AT91B_LED_MASK      (AT91B_LED1|AT91B_LED2)
#define AT91D_BASE_PIO_LED 	(AT91C_BASE_PIOA)
#define AT91D_ID_PIO_LED    (AT91C_ID_PIOA)

/*-------------------------------*/
/* JOYSTICK Position Definition  */
/*-------------------------------*/
#define AT91B_SW1    (1<<19)	/* PA19 / PGMD7  & RK   FIQ     13 */
#define AT91B_SW2    (1<<20)	/* PA20 / PGMD8  & RF   IRQ0    16 */

#define AT91B_BP1    (1<<19)	/* PA19 / PGMD7  & RK   FIQ     13 */
#define AT91B_BP2    (1<<20)	/* PA20 / PGMD8  & RF   IRQ0    16 */

#define AT91B_SW_MASK  (AT91B_SW1|AT91B_SW2)
#define AT91B_BP_MASK  (AT91B_BP1|AT91B_BP2)

#define AT91D_BASE_PIO_SW   (AT91C_BASE_PIOA)
#define AT91D_ID_PIO_SW     (AT91C_ID_PIOA)

/*--------------*/
/* Clocks       */
/*--------------*/
#define AT91B_MAIN_OSC        18432000               // Main Oscillator MAINCK
#define AT91B_MCK             ((18432000*73/14)/2)   // Output PLL Clock (48 MHz)

#endif /* AT91SAM7S-EK_H */
