class Timer
{
public:
	Timer(float time = 0.0f) : mTime(time)
	{}


	float getSeconds() const { return mTime; }
	float getMilliseconds() const { return mTime * 1000.0f; }
	

private:
	float mTime;
};