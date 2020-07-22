#include "../headers/TestSubEntityTool.h"

TestSubEntityTool::TestSubEntityTool()
{
}

void TestSubEntityTool::_OnRestartTool()
{
}

StatusInt TestSubEntityTool::_OnElementModify(EditElementHandleR eeh)
{
	SubEntity[] subEntities = new SubEntity[0];
	this.GetAcceptedSubEntities(ref subEntities);
	// Ok, I receive accepted faces

	for (int i = 0; i < subEntities.Length; i++)
	{
		SubEntity face = subEntities[i];

		IntPtr geom = default(IntPtr);
		BentleyStatus getGeometryStatus = this.GetSubEntityGeometry(geom, face);
		// getGeometryStatus is SUCCESS, but the pointer is always zero ... no data

		SubEntity[] vertices;
		BentleyStatus getFaceVerticesStatus = SolidUtil.GetFaceVertices(out vertices, face);
		// getFaceVerticesStatus is always ERROR
	}

	// Element is not modifed
	// From C++ documentation: ERROR to reject change or if change completely handled by tool.
	return StatusInt.Error;
	//return StatusInt();
}

UInt32 TestSubEntityTool::_GetSubEntityColor(ViewportR vp, ISubEntity::SubEntityType entityType, bool isDynamics)
{
	return  UInt32();
}
