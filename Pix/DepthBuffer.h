#pragma once

#include <memory>

class DepthBuffer
{
public:
	static DepthBuffer* Get();

	void OnNewFrame();

	void Initialize(int width, int height);

	void SetEnable(bool enable);
	bool CheckDepthBuffer(int x, int y, float depth);
private:
	std::unique_ptr<float[]> mDepthBuffer;
	int mWidth = 0;
	int mHeight = 0;
	bool mEnabled = false;
};