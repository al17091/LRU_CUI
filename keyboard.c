#include "keyboard.h"

enum keycode inputKey() {
    int kn = getchar(); //1:通常キー
    if (kn == 0x1b){
        kn = getchar(); //2:特殊キー
        if(kn==0x5b){
            kn=getchar();
            switch (kn)
            {
            case 0x41:  // ↑
                return up;
            case 0x42:  // ↓
                return down;
            case 0x43:  // →
                return right;
            case 0x44:  // ←
                return left;
            default:
                return other;
            }
        }else if(kn==0x1b){ //Twice Esc is exit(0).
            return Esc;
        }else{
            return other;
        }
    }else if(kn==0x71){
        return quit;
    }else if(kn==0x0a){
        return enter;
    }else{
        return other;
    }
	return other;
}