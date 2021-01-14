#pragma once
/**
 * @file GraphicsProcessor.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../headers/GraphicsProcessorHelper.h"

/** @ingroup data_processing Data Processing
*  @{
*/

namespace DataProcessing
{
	namespace GraphicsProperties
	{
		/**
		 * @brief Class for collecting graphical output of an element's Draw method.
		 * This class inherits and implement the Bentley IElementGraphicsProcessor Interface
		 * 
		 * @remark This class inherits and implement the Bentley IElementGraphicsProcessor Interface
	     * @see IElementGraphicsProcessor
		 */
		class GraphicsProcessor : public IElementGraphicsProcessor
		{
		public:
			/**
			 * @brief Get the Instance object
			 * 
			 * @return GraphicsProcessor* 
			 */
			static GraphicsProcessor* getInstance()
			{
				call_once(initInstanceFlag, &GraphicsProcessor::initGraphicsProcessor);
				return _GraphicsProcessor;
			};

			/**
			 * @brief Get the Graphics Processor Helper object
			 * 
			 * @return GraphicsProcessorHelper* 
			 */
			GraphicsProcessorHelper* getGraphicsProcessorHelper();
		private:
			GraphicsProcessor();

			Logging::Logger* _logger = Logging::Logger::getLogger();

			virtual BentleyStatus _ProcessTextString(TextStringCR text) override;
			virtual BentleyStatus _ProcessCurvePrimitive(ICurvePrimitiveCR curve, bool isClosed, bool isFilled) override;
			virtual BentleyStatus _ProcessCurveVector(CurveVectorCR curves, bool isFilled) override;
			virtual bool _ProcessAsFacets(bool isPolyface) const override;
			virtual bool _ProcessAsBody(bool isCurved) const override;
			virtual BentleyStatus _ProcessSurface(MSBsplineSurfaceCR surface) override;
			virtual BentleyStatus _ProcessBody(ISolidKernelEntityCR entity, IFaceMaterialAttachmentsCP attachments) override;
			virtual BentleyStatus _ProcessFacets(PolyfaceQueryCR meshData, bool isFilled) override;
			virtual BentleyStatus _ProcessSolidPrimitive(ISolidPrimitiveCR primitive) override;

			virtual void _AnnounceElemDisplayParams(ElemDisplayParamsCR displayParams) override;

			//! Supply the current context that is processing the geometry.
			//! @param[in] context The current view context.
			//virtual void _AnnounceContext(ViewContextR context)  override;

			//! Supply the current transform that subsequent geometry is displayed through.
			//! @param[in] trans The transform to apply to subsequent process calls.
			virtual void _AnnounceTransform(TransformCP trans)  override;

			static GraphicsProcessor* _GraphicsProcessor;
			static once_flag initInstanceFlag;
			static void initGraphicsProcessor()
			{
				_GraphicsProcessor = new GraphicsProcessor();
			}

			GraphicsProcessorHelper mGraphicsProcessorHelper;
			Transform m_currentTransform;
		};
	}
}
/** @} */ // end of Data Processing
