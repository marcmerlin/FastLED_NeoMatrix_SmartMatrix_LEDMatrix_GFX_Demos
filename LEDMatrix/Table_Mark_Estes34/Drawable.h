

#ifndef AuroraDrawable_H
#define AuroraDrawable_H

class AuroraDrawable{
public:
    char* name;

    virtual bool isRunnable() {
        return false;
    }
    
    virtual bool isPlaylist() {
        return false;
    }

    // a single frame should be drawn as fast as possible, without any delay or blocking
    // return how many millisecond delay is requested before the next call to drawFrame()
    virtual unsigned int drawFrame() {
	// not visible in this file (defined in neomatrix_config.h)
        //backgroundLayer.fillScreen({ 0, 0, 0 });
        return 0;
    };

    virtual void start() {};
    virtual void stop() {};
};

#endif
