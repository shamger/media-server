
#include "VideoLayerSelector.h"
#include "vp9/VP9LayerSelector.h"
#include "vp8/VP8LayerSelector.h"


BYTE VideoLayerSelector::MaxLayerId = 0xFF;

class DummyVideoLayerSelector : public VideoLayerSelector
{
public:
	DummyVideoLayerSelector(VideoCodec::Type codec)
	{
		this->codec = codec;
	}
	
	void SelectTemporalLayer(BYTE id) override {};
	void SelectSpatialLayer(BYTE id) override {};
	
	bool Select(RTPPacket *packet,bool &mark)	override 
	{
		mark = packet->GetMark();
		return true;
	}
	
	BYTE GetTemporalLayer() const override { return MaxLayerId; }
	BYTE GetSpatialLayer()	const override { return MaxLayerId;  }
	VideoCodec::Type GetCodec()	const override { return codec; }
private:
	VideoCodec::Type codec;
	
};

VideoLayerSelector* VideoLayerSelector::Create(VideoCodec::Type codec)
{
	
	switch(codec)
	{
		case VideoCodec::VP9:
			return new VP9LayerSelector();
		case VideoCodec::VP8:
			return new VP8LayerSelector();
		default:
			return new DummyVideoLayerSelector(codec);
	}
}