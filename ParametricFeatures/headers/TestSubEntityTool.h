#pragma once
#include "../enhancer/headers/GraphicsProcessorEnhancer.h"

public class TestSubEntityTool : public LocateSubEntityTool {

public:
	TestSubEntityTool();

	virtual void _OnRestartTool() override;

	virtual StatusInt _OnElementModify(EditElementHandleR eeh) override;

	virtual UInt32 _GetSubEntityColor(ViewportR vp, ISubEntity::SubEntityType entityType, bool isDynamics) override;

};
