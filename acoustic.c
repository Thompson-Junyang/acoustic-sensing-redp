// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include "rp.h"

// int main (int argc, char **argv) {
//     int unsigned period = 1000000; // uS
//     int unsigned led;

//     // index of blinking LED can be provided as an argument
//     if (argc > 1) {
//         led = atoi(argv[1]);
//     // otherwise LED 0 will blink
//     } else {
//         led = 0;
//     }
//     printf("Blinking LED[%u]\n", led);
//     led += RP_LED0;

//     // Initialization of API
//     if (rp_Init() != RP_OK) {
//         fprintf(stderr, "Red Pitaya API init failed!\n");
//         return EXIT_FAILURE;
//     }

//     int unsigned retries = 1000;
//     while (retries--){
//         rp_DpinSetState(led, RP_HIGH);
//         usleep(period/2);
//         rp_DpinSetState(led, RP_LOW);
//         usleep(period/2);
//     }

//     // Releasing resources
//     rp_Release();

//     return EXIT_SUCCESS;
// }


/* Red Pitaya C API example Generating signal pulse on an external trigger
* This application generates a specific signal */









//continuous wave
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// #include "rp.h"

// int main(int argc, char **argv){

//     /* Burst count */


//     /* Print error, if rp_Init() function failed */
//     if(rp_Init() != RP_OK){
//         fprintf(stderr, "Rp api init failed!\n");
//     }
//     for(int i = 2000; i <= 20000; i+=500){
//     rp_GenReset();

//     rp_GenWaveform(RP_CH_1, RP_WAVEFORM_SINE);
    
//         rp_GenFreq(RP_CH_1, i);


//             rp_GenAmp(RP_CH_1, 0.8);

//     rp_GenMode(RP_CH_1, RP_GEN_MODE_CONTINUOUS);
//     //rp_GenBurstCount(RP_CH_1, 1);
//     //rp_GenBurstRepetitions(RP_CH_1, 10000);     // set to 65536 for INF pulses
//     //rp_GenBurstPeriod(RP_CH_1, 5000);

//     rp_GenOutEnable(RP_CH_1);
//     rp_GenTriggerOnly(RP_CH_1);

    


//     printf("%d\n",i);
//         sleep(1);

//     }
    
// rp_Release();
// }



#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "rp.h"

#define M_PI 3.14159265358979323846

int main(int argc, char **argv){

    int i;
    int buff_size = 16384;

    /* Print error, if rp_Init() function failed */
    if(rp_Init() != RP_OK){
        fprintf(stderr, "Rp api init failed!\n");
    }

    float *t = (float *)malloc(buff_size * sizeof(float));
    float *x = (float *)malloc(buff_size * sizeof(float));
    float *y = (float *)malloc(buff_size * sizeof(float));

    for(i = 1; i < buff_size; i++){
        t[i] = (2 * M_PI) / buff_size * i;
    }

    for (int i = 0; i < buff_size; ++i){
        x[i] = sin(t[i]) + ((1.0/3.0) * sin(t[i] * 3));
        y[i] = (1.0/2.0) * sin(t[i]) + (1.0/4.0) * sin(t[i] * 4);
    }

    rp_GenSynchronise();

    rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY);
    rp_GenWaveform(RP_CH_2, RP_WAVEFORM_ARBITRARY);

    rp_GenArbWaveform(RP_CH_1, x, buff_size);
    rp_GenArbWaveform(RP_CH_2, y, buff_size);

    rp_GenAmp(RP_CH_1, 0.7);
    rp_GenAmp(RP_CH_2, 1.0);

    rp_GenFreq(RP_CH_1, 4000.0);
    rp_GenFreq(RP_CH_2, 4000.0);

    rp_GenOutEnable(RP_CH_1);
    rp_GenOutEnable(RP_CH_2);
    rp_GenTriggerOnly(RP_CH_1);
    rp_GenTriggerOnly(RP_CH_2);

    /* Releasing resources */
    free(y);
    free(x);
    free(t);
    rp_Release();

    //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
}