#pragma once
#include <Mmdeviceapi.h>
#include <Audioclient.h>
#include <Audiopolicy.h>
#include <Devicetopology.h>
#include <Endpointvolume.h>
#include "TempMacro.h"

namespace csric {
	class AudioProcess {
	
	private:
		WAVEFORMATEX waveFormatex;
		float* lPointDataQueue;//����ʱ��������Ҫ����
		float* rPointDataQueue;
		UINT32 queueMaxLength;
		UINT32 queueHead;

		//CalculateLogFreq
		int* windows;
		int density = FREQ_DENSITY;//nFreqs per octave 
		int octaves = FREQ_OCTAVES;
		int freqMin = FREQ_MIN;
		float Q = 1;

		//misc
		float* addWeight;
	public:
		int nHistograms;
		AudioProcess() {
			queueMaxLength = QUEUE_MAX_LENGTH;
			lPointDataQueue = new float[queueMaxLength];
			rPointDataQueue = new float[queueMaxLength];
			memset(lPointDataQueue, 0, queueMaxLength);
			memset(rPointDataQueue, 0, queueMaxLength);
			queueHead = 0;
		}
		~AudioProcess() {
			if (lPointDataQueue) {
				delete[] lPointDataQueue;
			}
			if (rPointDataQueue) {
				delete[] rPointDataQueue;
			}
			if (windows) {
				delete[] windows;
			}
		}

		HRESULT EnqueueFrames(BYTE* data, UINT32 numFramesAvailable);//����ԭʼ֡���ݣ�����lr����
		HRESULT SetFormat(WAVEFORMATEX* pwfx);
		void PrintStream();//������
		void CalculateLogFreq(float* value);
		float AvePeak();
	};


}