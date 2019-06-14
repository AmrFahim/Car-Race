#include "ADC_Driver.h"

double ADC1_Result=0;
void ADC1Seq3_Handler(void){
	 ADC1_Result= ADC1_SSFIFO3_R; 
	 ADC1_ISC_R |=(1<<3);
}

void ADC1_INIT(void){
	 //Enable the ADC clock using the RCGCADC register (see page 350)
	 SYSCTL_RCGCADC_R =(1<<1); //use ADC1
	 //Enable the clock to the appropriate GPIO modules via the RCGCGPIO register (see page 338)
	 SYSCTL_RCGC2_R |= 0x00000010; //clock for PortE
	 GPIO_PORTE_DIR_R &=~(1<<1); //make PE1 as input pin
	 //Set the GPIO AFSEL bits for the ADC input pins
	 GPIO_PORTE_AFSEL_R |=(1<<1); //Enable Alternative function of PE1 ,the default function is AIN2(ADC) 
   GPIO_PORTE_DEN_R &=~(1<<1); //Disable digital to enable analog(AIN2) at PE1
	 GPIO_PORTE_AMSEL_R |=(1<<1); //Enable analog PE1
	
	                 /**Sample Sequencer Configuration**/
	   //Ensure that the sample sequencer is disabled by clearing the corresponding ASENn bit in the
    //(ADCACTSS) register. Programming of the sample sequencers is allowed without having them enabled
	 ADC1_ACTSS_R &=~(1<<3); //Sample Sequencer is disabled
   //ADC Event Multiplexer Select (ADCEMUX)  	
   ADC1_EMUX_R =(0xF<<12);//This field(bits 12:15) selects the trigger source for Sample Sequencer 3 continuously sample
	//For each sample in the sample sequence, configure the corresponding input source in the ADCSSMUXn register
	 ADC1_SSMUX3_R =2; //AIN2 page 798
	 ADC1_SSCTL3_R =0x6; //ADC Sample Sequence Control 3 ,0110,Set IE0 and END0
	 ADC1_IM_R |=(1<<3); //ADC Interrupt Mask ,MASK3,SS3 Interrupt Mask
	 ADC1_ACTSS_R |=(1<<3); //Enable Sample Sequencer
	 ADC1_ISC_R |=(1<<3); //ADC Interrupt Status and Clear , SS3 Interrupt Status and Clear,Clear flag status
	 NVIC_EN1_R |= (1<<19);//Enable ADC1 SS3
}