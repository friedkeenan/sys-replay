#include <stdio.h>
#include <switch.h>
#include "sysmodule.h"

bool record_paused=true;
u64 time_elapsed=0;

int main(int argc,char **argv){
    record_paused=true;
    while(appletMainLoop()){
        
        svcSleepThread(1e+8L); //.1 seconds; needed so the Switch doesn't glitch out
        hidScanInput();
        u64 kDown=hidKeysDown(CONTROLLER_P1_AUTO);
        u64 kHeld=hidKeysHeld(CONTROLLER_P1_AUTO);
        
        if((kDown&KEY_ZL || kDown&KEY_ZR) && (kHeld&KEY_ZL && kHeld&KEY_ZR)){
            record_paused=!record_paused;
            time_elapsed=0;
        }
        
        if(!record_paused){
            time_elapsed++;
            if(kDown){
                FILE *fp=fopen("/replay.txt","a");
                fprintf(fp,"%ld %ld\n",time_elapsed,kDown);
                fclose(fp);
                time_elapsed=0;
            }
        }
        
    }
    return 0;
}
