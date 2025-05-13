/*
 * my_structures.h
 *
 *  Created on: May 6, 2025
 *      Author: daniele
 */

#ifndef SRC_MY_STRUCTURES_H_
#define SRC_MY_STRUCTURES_H_

typedef struct RCC_{ //RCC type
		unsigned int CR;
		unsigned int CFGR;
		unsigned int CIR;
		unsigned int APB2RSTR;
		unsigned int APB1RSTR;
		union{ //AHBENR
			unsigned int AHBENR;
			struct {
				unsigned DMA1EN:1;
				unsigned DMA2EN:1;
				unsigned SRAMEN:1;
				unsigned RES0:1;
				unsigned FLITFEN:1;
				unsigned FMCEN:1;
				unsigned CRCEN:1;
				unsigned RES1:9;
				unsigned GPIOHEN:1;
				unsigned GPIOAEN:1;
				unsigned GPIOBEN:1;
				unsigned GPIOCEN:1;
				unsigned GPIODEN:1;
				unsigned GPIOEEN:1;
				unsigned GPIOFEN:1;
				unsigned Res_GPIOGEN:1;
				unsigned TSCEN:1;
				unsigned RES2:3;
				unsigned ADC12EN:1;
				unsigned ADC34EN:1;
				unsigned RES3:2;
			};//AHBENR
		};// union_AHBENR
		union{
			unsigned int APB2ENR;
			struct{
				unsigned SYS_CFGEN:1;
				unsigned res_00:10;
				unsigned TIM1EN:1;
				unsigned SPI1EN:1;
				unsigned TIM8EN:1;
				unsigned USART1EN:1;
				unsigned SPI4EN:1;
				unsigned TIM15EN:1;
				unsigned TIM16EN:1;
				unsigned TIM17EN:1;
				unsigned res_01:1;
				unsigned TIM20EN:1;
				unsigned res_02:11;
			};
		};
		union{//APB1ENR
			unsigned int APB1ENR;
			struct{
				unsigned TIM2EN:1;
				unsigned TIM3EN:1;
				unsigned TIM4EN:1;
				unsigned APB1ENR_RES0:1;
				unsigned TIM6EN:1;
				unsigned TIM7EN:1;
				unsigned APB1ENR_RES1:5;
				unsigned WWDGEN:1;
				unsigned APB1ENR_RES2:2;
				unsigned SPI2EN:1;
				unsigned SP3EN:1;
				unsigned APB1ENR_RES3:1;
				unsigned USART2EN:1;
				unsigned USART3EN:1;
				unsigned UART4EN:1;
				unsigned UART5EN:1;
				unsigned I2C1EN:1;
				unsigned I2C2EN:1;
				unsigned USBEN:1;
				unsigned APB1ENR_RES4:1;
				unsigned CANEN:1;
				unsigned DAC2EN:1;
				unsigned APB1ENR_RES5:1;
				unsigned PWREN:1;
				unsigned DAC1EN:1;
				unsigned I2C3EN:1;
				unsigned APB1ENR_RES6:1;
			};
		};
		unsigned int BDCR;
		unsigned int CSR;
		unsigned int AHBRSTR;
		unsigned int CFGR2;
		unsigned int CFGR3;
}RCC_Type;

typedef struct GPIO{//GPIO Type
	union { //MODER
	    unsigned int MODER;
	    struct {
	    	unsigned MODER0:2;
	    	unsigned MODER1:2;
	    	unsigned MODER2:2;
	    	unsigned MODER3:2;
	    	unsigned MODER4:2;
	    	unsigned MODER5:2;
	    	unsigned MODER6:2;
	    	unsigned MODER7:2;
	    	unsigned MODER8:2;
	    	unsigned MODER9:2;
	    	unsigned MODER10:2;
	    	unsigned MODER11:2;
	    	unsigned MODER12:2;
	    	unsigned MODER13:2;
	    	unsigned MODER14:2;
	    	unsigned MODER15:2;
	    	};//moder
		};//union_moder
		unsigned int OTYPER;
		unsigned int OSPEEDR;
		unsigned int PUPDR;
		union { //IDR
		    unsigned int IDR;
		    struct {
		    	unsigned IDR0:1;
		    	unsigned IDR1:1;
		    	unsigned IDR2:1;
		    	unsigned IDR3:1;
		    	unsigned IDR4:1;
		    	unsigned IDR5:1;
		    	unsigned IDR6:1;
		    	unsigned IDR7:1;
		    	unsigned IDR8:1;
		    	unsigned IDR9:1;
		    	unsigned IDR10:1;
		    	unsigned IDR11:1;
		    	unsigned IDR12:1;
		    	unsigned IDR13:1;
		    	unsigned IDR14:1;
		    	unsigned IDR15:1;
		    	unsigned RES0:16;
		    };//IDR
		};//union_IDR
		union { //ODR
			unsigned int ODR;
			struct {
				unsigned ODR0:1;
				unsigned ODR1:1;
				unsigned ODR2:1;
				unsigned ODR3:1;
				unsigned ODR4:1;
				unsigned ODR5:1;
				unsigned ODR6:1;
				unsigned ODR7:1;
				unsigned ODR8:1;
				unsigned ODR9:1;
				unsigned ODR10:1;
				unsigned ODR11:1;
				unsigned ODR12:1;
				unsigned ODR13:1;
				unsigned ODR14:1;
				unsigned ODR15:1;
				unsigned RES1:16;
				};//ODR
		};//union_ODR
		unsigned int BSRR;
		unsigned int LCKR;
		union{
			unsigned int AFRL;
			struct{
				unsigned AFRLAFR0:4;
				unsigned AFRLAFR1:4;
				unsigned AFRLAFR2:4;
				unsigned AFRLAFR3:4;
				unsigned AFRLAFR4:4;
				unsigned AFRLAFR5:4;
				unsigned AFRLAFR6:4;
				unsigned AFRLAFR7:4;
			};
		};
		unsigned int AFRH;
		unsigned int BRR;
}GPIO_Type;

typedef struct TIMER{
	union{ //CR1
		unsigned int CR1;
		struct {
			unsigned CEN:1;
			unsigned UDIS:1;
			unsigned URS:1;
			unsigned OPM:1;
			unsigned DIR:1;
			unsigned CMS:2;
			unsigned ARPE:1;
			unsigned CKD:2;
			unsigned RES0:1;
			unsigned UIFREMA:1;
			unsigned RES2:20;
		};//Struct Cr1
	};//Union Cr1
	unsigned int CR2;
	unsigned int SMCR;
	union{ //DIER
		unsigned int DIER;
		struct{
			unsigned UIE:1;
			unsigned CC1IE:1;
			unsigned CC2IE:1;
			unsigned CC3IE:1;
			unsigned CC4IE:1;
			unsigned res_3:1;
			unsigned TIE:1;
			unsigned res_4:1;
			unsigned TDE:1;
			unsigned res_5:17;
		};
	};
	union{ //SR
		unsigned int SR;
		struct{
			unsigned UIF:1;
			unsigned CC1IF:1;
			unsigned CC2IF:1;
			unsigned CC3IF:1;
			unsigned CC4IF:1;
			unsigned RES_6:1;
			unsigned TIF:1;
			unsigned res_7:2;
			unsigned CC1OF:1;
			unsigned CC2OF:1;
			unsigned CC3OF:1;
			unsigned CC4OF:1;
			unsigned res_8:19;
		};//Struct SR
	};//UNION SR
	union{ //Union EGR
		unsigned int EGR;
		struct{
			unsigned UG:1;
			unsigned CC1G:1;
			unsigned CC2G:1;
			unsigned CC3G:1;
			unsigned CC4G:1;
			unsigned res_9:1;
			unsigned TG:1;
			unsigned res_10:25;
		};
	};
	unsigned int CCMR1;
	unsigned int CCMR2;
	unsigned int CCER;
	unsigned int CNT;
	unsigned int PSC;
	unsigned int ARR;
	unsigned int SR_RES0;
	unsigned int CCR1;
	unsigned int CCR2;
	unsigned int CCR3;
	unsigned int CCR4;
	unsigned int SR_RES1;
	unsigned int DCR;
	unsigned int DMAR;
}GP_TIMER_Type;

typedef struct ADC{
	union{ //ISR
		unsigned int ISR;
		struct {
			unsigned ADRDY:1;
			unsigned EOSMP:1;
			unsigned EOC:1;
			unsigned EOS:1;
			unsigned OVR:1;
			unsigned JEOC:1;
			unsigned JEOS:1;
			unsigned AWD1:1;
			unsigned AWD2:1;
			unsigned AWD3:1;
			unsigned JQOVF:1;
			unsigned res_ISR:21;
		};//Struct ISR
	};//Union ISR
	union{ //IER
		unsigned int IER;
		struct {
			unsigned ADRDYIE:1;
			unsigned EOSMPIE:1;
			unsigned EOCIE:1;
			unsigned EOSIE:1;
			unsigned OVRIE:1;
			unsigned JEOCIE:1;
			unsigned JEOSIE:1;
			unsigned AWD1IE:1;
			unsigned AWD2IE:1;
			unsigned AWD3IE:1;
			unsigned JQOVFIE:1;
			unsigned res_IER:21;
		};//Struct IER
	};//Union IER
	union{
		unsigned int CR;
		struct{
			unsigned ADEN:1;
			unsigned ADDIS:1;
			unsigned ADSTART:1;
			unsigned JADSTART:1;
			unsigned ADSTP:1;
			unsigned JADSPT:1;
			unsigned res_CR0:22;
			unsigned ADVREGEN:2;
			unsigned ADCALDIF:1;
			unsigned ADCAL:1;
		};//Struct CR
	};//Union CR
	union{//CFGR
		unsigned int CFGR;
		struct{
			unsigned DMAEN:1;
			unsigned DMACFG:1;
			unsigned res_CFGR0:1;
			unsigned RES:2;
			unsigned ALIGN:1;
			unsigned EXTSEL:4;
			unsigned EXTEN:2;
			unsigned OVRMOD:1;
			unsigned CONT:1;
			unsigned AUTDLY:1;
			unsigned res_CFGR1:1;
			unsigned DISCEN:1;
			unsigned DISCNUM:3;
			unsigned JDISCEN:1;
			unsigned JQM:1;
			unsigned AWD1SGL:1;
			unsigned AWD1EN:1;
			unsigned JAWD1EN:1;
			unsigned JAUTO:1;
			unsigned AWD1CH:5;
			unsigned res_CFGR2:1;
		}; //Struct CFGR
	};//Union CFGR
	unsigned int res_ADC0;
	union{//SMPR1
		unsigned int SMPR1;
		struct{
			unsigned res_SMPR0:3;
			unsigned SMP1:3;
			unsigned SMP2:3;
			unsigned SMP3:3;
			unsigned SMP4:3;
			unsigned SMP5:3;
			unsigned SMP6:3;
			unsigned SMP7:3;
			unsigned SMP8:3;
			unsigned SMP9:3;
			unsigned res_SMPR1:2;
		};//Struct SMPR1
	};//Union SMPR1
	union{//SMPR2
		unsigned int SMPR2;
		struct{
			unsigned SMP10:3;
			unsigned SMP11:3;
			unsigned SMP12:3;
			unsigned SMP13:3;
			unsigned SMP14:3;
			unsigned SMP15:3;
			unsigned SMP16:3;
			unsigned SMP17:3;
			unsigned SMP18:3;
			unsigned res_SMPR2:5;
		};//Struct SMPR2
	};//Union SMPR2
	unsigned int res_ADC1;
	union{//TR1
		unsigned int TR1;
		struct{
			unsigned LT1:12;
			unsigned res_TR0:4;
			unsigned HT1:12;
			unsigned res_TR1:4;
		};//Struct TR1
	};//Union TR1
	union{//TR2
		unsigned int TR2;
		struct{
			unsigned LT2:8;
			unsigned res_TR20:8;
			unsigned HT2:8;
			unsigned res_TR21:8;
		};//Struct TR2
	};//Union TR2
	union{//TR3
		unsigned int TR3;
		struct{
			unsigned LT3:8;
			unsigned res_TR30:8;
			unsigned HT3:8;
			unsigned res_TR31:8;
		};//Struct TR3
	};//Union TR3
	unsigned int res_ADC2;
	union{//SQR1
		unsigned int SQR1;
		struct{
			unsigned L:4;
			unsigned res_SQR10:2;
			unsigned SQ1:5;
			unsigned res_SQR11:1;
			unsigned SQ2:5;
			unsigned res_SQR12:1;
			unsigned SQ3:5;
			unsigned res_SQR13:1;
			unsigned SQ4:5;
			unsigned res_SQR14:3;
		};//Struct SQR1
	};//Union SQR1
	union{//SQR2
		unsigned int SQR2;
		struct{
			unsigned SQ5:5;
			unsigned res_SQR20:1;
			unsigned SQ6:5;
			unsigned res_SQR21:1;
			unsigned SQ7:5;
			unsigned res_SQR22:1;
			unsigned SQ8:5;
			unsigned res_SQR23:1;
			unsigned SQ9:5;
			unsigned res_SQR24:3;
		};//Struct SQR2
	};//Union SQR2
	union{ //SQR3
		unsigned int SQR3;
		struct {
			unsigned SQ10:5;
			unsigned res_SQR30:1;
			unsigned SQ11:5;
			unsigned res_SQR31:1;
			unsigned SQ12:5;
			unsigned res_SQR32:1;
			unsigned SQ13:5;
			unsigned res_SQR33:1;
			unsigned SQ14:5;
			unsigned res_SQR34:3;
		};//Struct SQR3
	};//Union SQR3
	union{ //SQR4
		unsigned int SQR4;
		struct{
			unsigned SQ15:5;
			unsigned res_SQR40:1;
			unsigned SQ16:5;
			unsigned res_SQR41:21;
		};//Struct SQR4
	}; //Union SQR4
	union{
		unsigned int DR;
		struct {
			unsigned RDATA:16;
			unsigned RES_DR:16;
		};//Struct DR
	};//Union DR
	unsigned int res_ADC3;
	unsigned int res_ADC4;
	union {//JSQR
		unsigned int JSQR;
		struct {
			unsigned JL:2;
			unsigned JEXTSEL:4;
			unsigned JEXTEN:2;
			unsigned JSQ1:5;
			unsigned res_JSQR0:1;
			unsigned JSQ2:5;
			unsigned res_JSQR1:1;
			unsigned JSQ3:5;
			unsigned res_JSQR2:1;
			unsigned JSQ4:5;
			unsigned res_JSQR3:1;
		};//Struct JSQR
	};//Union JSQR
	unsigned int res_ADC5;
	unsigned int res_ADC6;
	unsigned int res_ADC7;
	unsigned int res_ADC8;
	union{ //OFR1
		unsigned int OFR1;
		struct {
			unsigned OFFSET1:12;
			unsigned res_OFR0:14;
			unsigned OFFSET1_CH:5;
			unsigned OFFSET1_EN:1;
		};//Struct OFR1
	};//Union OFR1
	union{ //OFR2
		unsigned int OFR2;
		struct {
			unsigned OFFSET2:12;
			unsigned res_OFR1:14;
			unsigned OFFSET2_CH:5;
			unsigned OFFSET2_EN:1;
		};//Struct OFR2
	};//Union OFR2
	union{ //OFR3
		unsigned int OFR3;
		struct {
			unsigned OFFSET3:12;
			unsigned res_OFR2:14;
			unsigned OFFSET3_CH:5;
			unsigned OFFSET3_EN:1;
		};//Struct OFR3
	};//Union OFR3
	union{ //OFR4
		unsigned int OFR4;
		struct {
			unsigned OFFSET4:12;
			unsigned res_OFR3:14;
			unsigned OFFSET4_CH:5;
			unsigned OFFSET4_EN:1;
		};//Struct OFR4
	};//Union OFR4
	unsigned int res_ADC9;
	unsigned int res_ADC10;
	unsigned int res_ADC11;
	unsigned int res_ADC12;
	union{ //JDR1
		unsigned int JDR1;
		struct {
			unsigned JDATA1:16;
			unsigned res_JDR10:16;
		};//Struct JDR1
	};//Union JDR1
	union{ //JDR2
		unsigned int JDR2;
		struct {
			unsigned JDATA2:16;
			unsigned res_JDR20:16;
		};//Struct JDR2
	};//Union JDR2
	union{ //JDR3
		unsigned int JDR3;
		struct {
			unsigned JDATA3:16;
			unsigned res_JDR30:16;
		};//Struct JDR3
	};//Union JDR3
	union{ //JDR4
		unsigned int JDR4;
		struct {
			unsigned JDATA4:16;
			unsigned res_JDR40:16;
		};//Struct JDR4
	};//Union JDR4
	unsigned int res_ADC13;
	unsigned int res_ADC14;
	unsigned int res_ADC15;
	unsigned int res_ADC16;
	union{//AWD2CR
		unsigned int AWD2CR;
		struct {
			unsigned res_AWD2CR0:1;
			unsigned AWD2CH:18;
			unsigned res_AWD2CR1:13;
		};//Struct AWD2CR
	};//Union AWD2CR
	union{//AWD3CR
		unsigned int AWD3CR;
		struct {
			unsigned res_AWD3CR0:1;
			unsigned AWD3CH:18;
			unsigned res_AWD3CR1:13;
		};//Struct AWD3CR
	};//Union AWD3CR
	unsigned int res_ADC17;
	unsigned int res_ADC18;
	union{//DIFSEL
		unsigned int DIFSEL_register;
		struct {
			unsigned res_DIFSEL0:1;
			unsigned DIFSEL:18;
			unsigned res_DIFSEL1:13;
		};//Struct DIFSEL
	};//Union DIFSEL
	union{//CALFACT
		unsigned int CALFACT;
		struct {
			unsigned CALFACT_S:7;
			unsigned res_CALFACT0:9;
			unsigned CALFACT_D:7;
			unsigned res_CALFACT1:9;
		};//Struct CALFACT
	};//Union CALFACT
}ADC_Type;

typedef struct ADC_COMMON{
	union{//CSR
		unsigned int CSR;
		struct {
			unsigned ADRDY_MST:1;
			unsigned EOSMP_MST:1;
			unsigned EOC_MST:1;
			unsigned EOS_MST:1;
			unsigned OVR_MST:1;
			unsigned JEOC_MST:1;
			unsigned JEOS_MST:1;
			unsigned AWD1_MST:1;
			unsigned AWD2_MST:1;
			unsigned AWD3_MST:1;
			unsigned JQOVF_MST:1;
			unsigned res_CSR0:5;
			unsigned ADRDY_SLV:1;
			unsigned EOSMP_SLV:1;
			unsigned EOC_SLV:1;
			unsigned EOS_SLV:1;
			unsigned OVR_SLV:1;
			unsigned JEOC_SLV:1;
			unsigned JEOS_SLV:1;
			unsigned AWD1_SLV:1;
			unsigned AWD2_SLV:1;
			unsigned AWD3_SLV:1;
			unsigned JQOVF_SLV:1;
			unsigned res_CSR1:5;
		};//Struct CSR
	};//Union CSR
	unsigned int res_ADC_COMMON_0;
	union{//CCR
		unsigned int CCR;
		struct {
			unsigned DUAL:5;
			unsigned res_CCR0:3;
			unsigned DELAY:4;
			unsigned res_CCR1:1;
			unsigned DMACFG:1;
			unsigned MDMA:2;
			unsigned CKMODE:2;
			unsigned res_CCR2:4;
			unsigned VREFEN:1;
			unsigned TSEN:1;
			unsigned VBATEN:1;
			unsigned res_CCR3:7;
		};//Struct CCR
	};//Union CCR
	union{//CDR
		unsigned int CDR;
		struct {
			unsigned RDATA_MST:16;
			unsigned RDATA_SLV:16;
		};//Struct CDR
	};//Union CDR
}ADC_COMMON_Type;

typedef struct DAC{
	union{ //Union CR
		unsigned int CR;
		struct {
			unsigned EN1:1;
			unsigned BOFF1:1;
			unsigned TEN1:1;
			unsigned TSEL1:3;
			unsigned WAVE1:2;
			unsigned MAMP1:4;
			unsigned DMAEN1:1;
			unsigned DMAUDRIE1:1;
			unsigned res_cr0:2;
			unsigned EN2:1;
			unsigned BOFF2:1;
			unsigned TEN2:1;
			unsigned TSEL2:3;
			unsigned WAVE2:2;
			unsigned MAMP2:4;
			unsigned DMAEN2:1;
			unsigned DMAUDRIE2:1;
			unsigned res_cr1:2;
		}; //Struct CR
	}; //END Union CR
	union{ // Union SWTRIG
	unsigned int SWTRIGR;
	struct {
		unsigned SWTRIG1:1;
		unsigned SWTRIG2:1;
		unsigned res_swtrig0:30;
		}; //END Struct SWTRIG
	}; //END Union SWTRIG
	union {//Union DHR12R1
		unsigned int DHR12R1;
		struct {
			unsigned DACC1DHRR1:12;
			unsigned res_dhr0:20;
		};
	};
	union{//Union DHR12L1
		unsigned int DHR12L1;
		struct{
			unsigned res_dhr1:4;
			unsigned DACC1DHRL1:12;
			unsigned res_dhr2:16;
		};
	};// End union DHR12L1
	union{//Union DHR8R1
		unsigned int DHR8R1;
		struct{
			unsigned DACC1DHR8R1:8;
			unsigned res_dhr3:24;
		};
	};//End Union DHR8R1
	union{// Union DHR12R2
		unsigned int DHR12R2;
		struct{
			unsigned DACC2DHRR2:12;
			unsigned resdhr4:20;
		};
	}; //End Union DHR12R2
	union{// Union DHR12L2
		unsigned int DHR12L2;
		struct{
			unsigned res_dhr5:4;
			unsigned DACC2DHRL2:12;
			unsigned res_dhr6:16;
		};
	};
	union{//Union DHR8R2
		unsigned int DHR8R2;
		struct{
			unsigned DACC1DHR8R2:8;
			unsigned res_dhr7:24;
		};
	}; //End Union DHR8R2
	union{//Union DHR12RD
		unsigned int DHR12RD;
		struct{
			unsigned DACC1DHRRD:12;
			unsigned res_dhr8:4;
			unsigned DACC2DHRRD:12;
			unsigned res_dhr9:4;
		};
	};
	union{//Union DHR12LD
		unsigned int DHR12LD;
		struct{
			unsigned res_dhr10:4;
			unsigned DACC1DHRLD:12;
			unsigned res_dhr11:4;
			unsigned DACC2DHRLD:12;
		};
	};
	union{//Union DHR8RD
		unsigned int DHR8RD;
		struct{
			unsigned DACC1DHR8RD:8;
			unsigned DACC2DHR8RD:8;
			unsigned res_dhr12:16;
		};
	};
	union{//Union DOR1
		unsigned int DOR1;
		struct{
			unsigned DACC1DOR:12;
			unsigned res_dhr13:20;
		};
	};
	union{//Union DOR2
		unsigned int DOR2;
		struct{
			unsigned DACC2DOR:12;
			unsigned res_dhr14:20;
		};
	};
	union{ //Union SR
		unsigned int SR;
		struct{
			unsigned res_dhr15:13;
			unsigned DMAUDR1:1;
			unsigned res_dhr16:15;
			unsigned DMAUDR2:1;
			unsigned res_dhr17:2;
		};
	};
}DAC_Type;

typedef struct USART{
	union{ //CR1
		unsigned int CR1;
		struct{
			unsigned UE:1;
			unsigned UESM:1;
			unsigned RE:1;
			unsigned TE:1;
			unsigned IDLEIE:1;
			unsigned RXNEIE:1;
			unsigned TCIE:1;
			unsigned TXEIE:1;
			unsigned PEIE:1;
			unsigned PS:1;
			unsigned PCE:1;
			unsigned WAKE:1;
			unsigned M0:1;
			unsigned MME:1;
			unsigned CMIE:1;
			unsigned OVER8:1;
			unsigned DEDT0:1;
			unsigned DEDT1:1;
			unsigned DEDT2:1;
			unsigned DEDT3:1;
			unsigned DEDT4:1;
			unsigned DEAT0:1;
			unsigned DEAT1:1;
			unsigned DEAT2:1;
			unsigned DEAT3:1;
			unsigned DEAT4:1;
			unsigned RTOIE:1;
			unsigned EOBIE:1;
			unsigned M1:1;
			unsigned res_usart0:3;
		};
	}; //End union CR1
	union{ //CR2
			unsigned int CR2;
			struct{
				unsigned res_usart1:4;
				unsigned ADDM7:1;
				unsigned LBDL:1;
				unsigned LBDIE:1;
				unsigned res_usart2:1;
				unsigned LBCL:1;
				unsigned CPHA:1;
				unsigned CPOL:1;
				unsigned CLKEN:1;
				unsigned STOP:2;
				unsigned LINEN:1;
				unsigned SWAP:1;
				unsigned RXINV:1;
				unsigned TXINV:1;
				unsigned DATAINV:1;
				unsigned MSBFIRST:1;
				unsigned ABREN:1;
				unsigned ABRMOD0:1;
				unsigned ABRMOD1:1;
				unsigned RTOEN:1;
				unsigned ADD1:4;
				unsigned ADD2:4;
			};
	};
	unsigned int CR3;
	unsigned int BRR;
	unsigned int GTPR;
	unsigned int RTOR;
	unsigned int RQR;
	union{
			unsigned int ISR;
			struct{
				unsigned PE:1;
				unsigned FE:1;
				unsigned NF:1;
				unsigned ORE:1;
				unsigned IDLE:1;
				unsigned RXNE:1;
				unsigned TC:1;
				unsigned TXE:1;
				unsigned LBDF:1;
				unsigned CTSIF:1;
				unsigned CTS:1;
				unsigned RTOF:1;
				unsigned EOBF:1;
				unsigned res_00:1;
				unsigned ABRE:1;
				unsigned ABRF:1;
				unsigned BUSY:1;
				unsigned CMF:1;
				unsigned SBKF:1;
				unsigned RWU:1;
				unsigned WUF:1;
				unsigned TEACK:1;
				unsigned REACK:1;
				unsigned res_01:9;
			};
	};
	unsigned int ICR;
	unsigned int RDR;
	unsigned int TDR;
}USART_Type;

// Memory locations
#define RCC ((RCC_Type*) 0x40021000) //Indirizzo di Base RCC
#define GPIOA ((GPIO_Type*) 0x48000000) //Indirizzo di base GPIOA
#define GPIOC ((GPIO_Type*) 0x48000800) //Indirizzo base GPIOC (USART1)
#define GPIOD ((GPIO_Type*) 0x48000C00) //Indirizzo base GPIOD (Display 0-7)
#define GPIOE ((GPIO_Type*) 0x48001000) //Indirizzo di base GPIOE

#define TIM2 ((GP_TIMER_Type*) 0x40000000) //Indirizzo base timer 2
#define TIM3 ((GP_TIMER_Type*) 0x40000400) //Indirizzo base timer 3
#define TIM4 ((GP_TIMER_Type*) 0x40000800) //Indirizzo timer 4

#define ADC1 ((ADC_Type*) 0x50000000) //Indirizzo base ADC1
#define ADC2 ((ADC_Type*) 0x50000100) //Indirizzo base ADC2
#define ADC12 ((ADC_COMMON_Type*) 0x50000300) //Indirizzo comune ADC12

#define DAC1 ((DAC_Type*) 0x40007400) //Indirizzo base DAC1

#define USART1 ((USART_Type*) 0x40013800) //Indirizzo base USART1

#define LED_8 (GPIOE->ODR8)
#define USER_BTN (GPIOA->IDR0)




#endif /* SRC_MY_STRUCTURES_H_ */
