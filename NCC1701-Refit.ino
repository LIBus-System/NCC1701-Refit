// Audio objects

#include <DTWI.h>
#include <PCM1774.h>
#include <TPA2016.h>
#include <I2S.h>

DTWI0 intWire;
PCM1774 dac(intWire);
TPA2016 amp(intWire, PIN_AMP);
I2S i2s(22050);

// Control objects

#include <DebouncedInput.h>

DebouncedInput redAlertButton(0, 20, true);

// LIBus objects

#include <LIBus.h>
#include <LIBusGeneral.h>
#include <LIBusSpinner.h>
#include <Animation.h>

#define DEFLECTOR 0x30756A
#define SAUCER 0x20ABF3
#define MAINSEC 0x20DFA9

LIBusMaster libus;
//LIBusGeneral saucer(libus, SAUCER);
//LIBusGeneral mainsec(libus, MAINSEC);
//LIBusSpinner deflector(libus, DEFLECTOR);

// SD Card objects

#include <DSDVOL.h>
#include <USB_MSD.h>

DefineSDSPI(dSDSpi);
DefineDSDVOL(dSDVol, dSDSpi);
FRESULT fr;

// USB objects
USBHS usbDevice;
USBManager USB(usbDevice, 0xF055, 0x1701, "Majenko Technologies", "NCC-1701", "7412.6");
CDCACM uSerial;
USB_MSD msd(dSDVol);

#include <CLI.h>

#define ANIM_ABSOLUTE(ADD, LED, VAL) \
    Animation::LIBUS_SEND, U24(ADD), 0x01, 2, LED, VAL

#define ANIM_FADE(ADD, LED, VAL, SPEED) \
    Animation::LIBUS_SEND, U24(ADD), 0x02, 4, LED, VAL, U16(SPEED)

#define ANIM_BLINK(ADD, LED, MARKT, SPACET, MARKV, SPACEV) \
    Animation::LIBUS_SEND, U24(ADD), 0x03, 7, LED, U16(MARKT), U16(SPACET), MARKV, SPACEV
    
#define ANIM_STROBE(ADD, LED, MARKT, SPACET, BREAKT, BLINKS, MARKV, SPACEV, BREAKV) \
    Animation::LIBUS_SEND, U24(ADD), 0x04, 11, LED, U16(MARKT), U16(SPACET), U16(BREAKT), BLINKS, MARKV, SPACEV, BREAKV

#define ANIM_SYNC(ADD, LED, REF) \
    Animation::LIBUS_SEND, U24(ADD), 0x05, 2, LED, REF

#define ANIM_FLICKER(ADD, LED, MINV, MAXV, SPEED) \
    Animation::LIBUS_SEND, U24(ADD), 0x06, 5, LED, MINV, MAXV, U16(SPEED)


const uint8_t shipBootProg[] = {

    Animation::FILE_OPEN, 0, 
        'm', 'o', 'n', 'o', '-', '0', '2', ' ', 'L', 'e', 'a', 'v', 'i', 'n', 'g', ' ', 
        'D', 'r', 'y', 'd', 'o', 'c', 'k', '.', 'w', 'a', 'v', 0,

    Animation::FILE_OPEN, 1, 
        'm', 'o', 'n', 'o', '-', '5', '5', ' ', 'R', 'e', 'd', ' ', 'A', 'l', 'e', 'r', 't', ' ', 
        'K', 'l', 'a', 'x', 'o', 'n', 's', ' ', '#', '2', '.', 'w', 'a', 'v', 0,

    Animation::FILE_OPEN, 2, 
        'm', 'o', 'n', 'o', '-', '5', '5', ' ', 'R', 'e', 'd', ' ', 'A', 'l', 'e', 'r', 't', ' ', 
        'K', 'l', 'a', 'x', 'o', 'n', 's', ' ', '#', '2', '.', 'w', 'a', 'v', 0,

    Animation::LIBUS_SEND, U24(DEFLECTOR), 0x20, 0, // Set mode 0 - animations, not spinning.

    ANIM_SYNC(DEFLECTOR, 3, 0),
    ANIM_SYNC(DEFLECTOR, 6, 0),
    ANIM_SYNC(DEFLECTOR, 9, 0),
    ANIM_SYNC(DEFLECTOR, 12, 0),
    ANIM_SYNC(DEFLECTOR, 15, 0),
    ANIM_SYNC(DEFLECTOR, 18, 0),
    ANIM_SYNC(DEFLECTOR, 21, 0),
    ANIM_SYNC(DEFLECTOR, 24, 0),
    ANIM_SYNC(DEFLECTOR, 27, 0),
    ANIM_SYNC(DEFLECTOR, 30, 0),
    ANIM_SYNC(DEFLECTOR, 33, 0),

    ANIM_SYNC(DEFLECTOR, 4, 1),
    ANIM_SYNC(DEFLECTOR, 7, 1),
    ANIM_SYNC(DEFLECTOR, 10, 1),
    ANIM_SYNC(DEFLECTOR, 13, 1),
    ANIM_SYNC(DEFLECTOR, 16, 1),
    ANIM_SYNC(DEFLECTOR, 19, 1),
    ANIM_SYNC(DEFLECTOR, 22, 1),
    ANIM_SYNC(DEFLECTOR, 25, 1),
    ANIM_SYNC(DEFLECTOR, 28, 1),
    ANIM_SYNC(DEFLECTOR, 31, 1),
    ANIM_SYNC(DEFLECTOR, 34, 1),

    ANIM_SYNC(DEFLECTOR, 5, 2),
    ANIM_SYNC(DEFLECTOR, 8, 2),
    ANIM_SYNC(DEFLECTOR, 11, 2),
    ANIM_SYNC(DEFLECTOR, 14, 2),
    ANIM_SYNC(DEFLECTOR, 17, 2),
    ANIM_SYNC(DEFLECTOR, 20, 2),
    ANIM_SYNC(DEFLECTOR, 23, 2),
    ANIM_SYNC(DEFLECTOR, 26, 2),
    ANIM_SYNC(DEFLECTOR, 29, 2),
    ANIM_SYNC(DEFLECTOR, 32, 2),
    ANIM_SYNC(DEFLECTOR, 35, 2),

    Animation::SOUND_SAMPLERATE, U32(16000),

    Animation::SOUND_VOLUME, 50,
    Animation::SOUND_DGAIN, 0,
    Animation::SOUND_AGAIN, 2,
    Animation::SOUND_BASS, 12,
    Animation::SOUND_MID, 6,
    Animation::SOUND_TREBLE, 3,
    Animation::SOUND_3D, 0, 15,
    
    // Play a file (file number 0) in stereo at 100% volume
    Animation::PLAY_MONO_BOTH, 0, 100, 

    ANIM_FADE(DEFLECTOR, 36, 80, 20),
    ANIM_FADE(DEFLECTOR, 37, 40, 30),

    Animation::DELAY, U16(3000),

    ANIM_FADE(DEFLECTOR, 36, 255, 20),
    ANIM_FADE(DEFLECTOR, 37, 100, 20),

    Animation::DELAY, U16(2000),

    ANIM_FADE(DEFLECTOR, 0, 255, 20),
    ANIM_FADE(DEFLECTOR, 1, 255, 20),

    Animation::DELAY, U16(2000),

    ANIM_FADE(DEFLECTOR, 36, 0, 5),
    ANIM_FADE(DEFLECTOR, 37, 0, 5),

    Animation::DELAY, U16(2000),

    ANIM_FADE(DEFLECTOR, 2, 255, 5),
    ANIM_FADE(DEFLECTOR, 0, 0, 5),
    ANIM_FADE(DEFLECTOR, 1, 0, 5),
    ANIM_FADE(DEFLECTOR, 38, 255, 5),

    Animation::DELAY, U16(1000),

    ANIM_FLICKER(DEFLECTOR, 38, 50, 255, 1),

    Animation::END
};

Animation shipBoot(shipBootProg);

const uint8_t deflectorPowerdown[] = {
    ANIM_FADE(DEFLECTOR, 38, 0, 5),
    ANIM_FADE(DEFLECTOR, 2, 0, 5),
    ANIM_FADE(DEFLECTOR, 0, 255, 5),
    ANIM_FADE(DEFLECTOR, 1, 150, 5),

    Animation::DELAY, U16(2000),

    ANIM_FADE(DEFLECTOR, 36, 255, 20),
    ANIM_FADE(DEFLECTOR, 37, 100, 20),

    Animation::DELAY, U16(2000),

    ANIM_FADE(DEFLECTOR, 0, 0, 20),
    ANIM_FADE(DEFLECTOR, 1, 0, 20),

    Animation::DELAY, U16(3000),

    ANIM_FADE(DEFLECTOR, 36, 0, 20),
    ANIM_FADE(DEFLECTOR, 37, 0, 40),

    Animation::END
};

const uint8_t redAlertProg[] = {
    ANIM_BLINK(SAUCER, 0, 100, 100, 255, 0),

    Animation::PLAY_MONO_LEFT, 1, 80, 
    Animation::DELAY, U16(1000),
    Animation::PLAY_MONO_RIGHT, 2, 20, 
    
    Animation::PLAY_WAITEND, 2,

    ANIM_ABSOLUTE(SAUCER, 0, 0),
    Animation::END
};

Animation redAlert(redAlertProg);

void findDevices2(Stream *dev, uint8_t type, uint8_t add1) {
    for (int i = 0; i < 0xFF; i++) {
        if (libus.areYouThere((type << 16) | (add1 << 8) | i)) {
            dev->printf("Device found at %06x\r\n", (type << 16) | (add1 << 8) | i);
        }
    }
}

void findDevices1(Stream *dev, uint8_t type) {
    for (int i = 0; i < 0xFF; i++) {
        if (libus.areYouThere((type << 16) | (i << 8) | 0xFF)) {
            findDevices2(dev, type, i);
        }
    }
}

void findDevices(Stream *dev) {
    for (int i = 0; i < 0xff; i++) {
        if (libus.areYouThere((i << 16) | 0xFFFF)) {
            findDevices1(dev, i);
        }
    }
}


CLI_COMMAND(scanForLibusDevices) {
    dev->println("Scanning for devices...");
    findDevices(dev);
    dev->println("Done.");
    return 0;
}

CLI_COMMAND(listFiles) {

    FRESULT fr;

    fr = DDIRINFO::fsopendir("/");
    if (fr != FR_OK) {
        dev->printf("Unable to open /: %d\r\n", fr);
        return 10;
    }

    fr = DDIRINFO::fsreaddir();
    while (fr == FR_OK) {
        if (strlen(DDIRINFO::fsget8Dot3Filename()) == 0) {
            break;
        }

        dev->printf("%10d %s\r\n", DDIRINFO::fsgetFileSize(), DDIRINFO::fsget8Dot3Filename());
        fr = DDIRINFO::fsreaddir();
    }

    DDIRINFO::fsclosedir();

    return 0;
}

DFILE rxFile;
uint16_t rxOffset = 0;

static inline uint8_t h2d(uint8_t hex) {
    if(hex > 0x39) hex -= 7; // adjust for hex letters upper or lower case
    return(hex & 0xf);
}

static inline uint8_t h2d2(uint8_t h, uint8_t l) {
    return h2d(h) << 4 | h2d(l);
}

void hexCapture(CLIClient *dev, char *data, int len) {

    if ((len > 0) && (data[0] == ':')) {
        uint8_t bytes = (len - 1) / 2;
        for (int i = 0; i < bytes; i++) {
            data[i] = h2d2(data[i*2+1], data[i*2+2]);
        }

        len = bytes;
        
        uint8_t dlen = data[0];
        uint16_t addr = data[2] | (data[1] << 8);
        uint8_t type = data[3];
        uint8_t cs = data[len-1];

        switch(type) {
            case 0x01: {
                dev->redirectEnd();
                dev->println("File received.");
                rxFile.fsclose();
                dev->setPrompt("> ");
                dev->print("> ");
                return;
            }
            break;
            
            case 0x04: { // Set address offset
                rxOffset = data[5] | (data[4] << 8);
            }
            break;
    
            case 0x00: { // Data
                uint32_t fullAddr = (rxOffset << 16) | addr;
                rxFile.fslseek(fullAddr);
                for (int i = 0; i < dlen; i++) {
                    rxFile.write(data[4+i]);
                }
            }
            break;
    
            default: {
            }
            break;
        }
    }
    dev->print("| ");    
}

CLI_COMMAND(receiveFile) {
    FRESULT fr;
    if (argc != 2) {
        dev->println("Usage: receive <filename.ext>");
        dev->println();
        dev->println("This command will receive Intel HEX (IHEX) formatted data,");
        dev->println("interpret it to binary, and save the data to the file specified.");
        return 10;
    }

    fr = rxFile.fsopen(argv[1], FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
    if (fr != FR_OK) {
        return fr;
    }
    rxOffset = 0;
    dev->setPrompt("| ");
    dev->redirectStart(hexCapture);
    
    return 0;
}

CLI_COMMAND(catFile) {
    if (argc != 2) {
        dev->printf("Usage: %s <file.ext>\r\n", argv[0]);
        return 10;
    }
    DFILE f;
    FRESULT fr = f.fsopen(argv[1], FA_READ);
    if (fr != FR_OK) {
        return fr;
    }

    char buf[80];
    uint32_t br;
    
    fr = f.fsread(buf, 80, &br);
    while (br > 0) {
        for (int i = 0; i < br; i++) {
            dev->write(buf[i]);
        }
        fr = f.fsread(buf, 80, &br);
    }
    f.fsclose();
    return 0;    
}

CLI_COMMAND(deleteFile) {
    if (argc != 2) {
        dev->printf("Usage: %s <file.ext>\r\n", argv[0]);
        return 10;
    }
    return DFATFS::fsunlink(argv[1]);
}

CLI_COMMAND(doReset) {
    executeSoftReset(0);
    return 0;
}

void setup() {
    USB.addDevice(uSerial);
    USB.addDevice(msd);
    USB.begin();
    
    redAlertButton.begin();

    libus.begin();

    Animation::setLIBus(libus);
    Animation::setI2S(i2s);
    Animation::setDAC(dac);
    Animation::setAMP(amp);

    dac.begin();
    amp.begin();
    i2s.begin();

    if ((fr = DFATFS::fsmount(dSDVol, DFATFS::szFatFsVols[0], 1)) != FR_OK) {
        uSerial.printf("Unable to mount SD card: %d\r\n", fr);
    }

    CLI.setDefaultPrompt("> ");
    CLI.addCommand("scan", scanForLibusDevices);
    CLI.addCommand("ls", listFiles);
    CLI.addCommand("dir", listFiles);
    CLI.addCommand("receive", receiveFile);
    CLI.addCommand("cat", catFile);
    CLI.addCommand("type", catFile);
    CLI.addCommand("reset", doReset);
    CLI.addCommand("rm", deleteFile);
    CLI.addCommand("del", deleteFile);
    CLI.addClient(uSerial);

    
 //   shipBoot.start();
}

void loop() {
    CLI.process();
    
    shipBoot.execute();
    redAlert.execute();
   
    if (redAlertButton.changedTo(LOW)) {
        redAlert.start();
    }
}
