#ifndef IMP_TIME
#define IMP_TIME

class ImpTimer
{
public:
    ImpTimer();
    ~ImpTimer();

    void start();
    void stop();
    void paused();
    void unpaused();

    int get_ticks();

    bool is_started();
    bool is_paused();
private:
    int startTick;
    int pausedTick;

    bool isPaused;
    bool isStarted;
};

#endif // IMP_TIME
