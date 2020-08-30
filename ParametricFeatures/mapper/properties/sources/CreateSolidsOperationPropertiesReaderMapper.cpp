#include "../headers/CreateSolidsOperationPropertiesReaderMapper.h"
//
//void CreateSolidsOperationPropertiesReaderMapper::mapCreateSolidsOperationPropertiesToReaderProperties(string labelValue, ECValue eCValue, ReaderProperties & readerProperties)
//{
//	// TODO [MP] to be removed or/and replaced
//	/*if (readerProperties.getSmartFeatureGeneralProperties()->getSmartFeatureTypeEnum() == SmartFeatureTypeEnum::CREATE_SOLIDS)
//	{
//		CreateSolidsOperationProperties* solidsOperationProperties = new CreateSolidsOperationProperties();
//
//		CreateSolidFunctionsEnum solidFunctionsEnum = readerProperties.getSmartFeatureGeneralProperties()->getCreateSolidTypeEnum();
//
//		solidsOperationProperties->setCreateSolidTypeEnum(solidFunctionsEnum);
//
//		switch (solidFunctionsEnum)
//		{
//			case CreateSolidFunctionsEnum::EXTRUDE:
//			{				
//				ExtrusionReaderProperties* extrusionReaderProperties = new ExtrusionReaderProperties();
//
//				if (CreateSolidFunctionsEnumUtils::getSolidPropertiesEnumByClassName(labelValue) == CreateSolidPropertiesEnum::THICKNESS)
//					if (!eCValue.IsNull())
//						extrusionReaderProperties->setThickness(eCValue.GetDouble());
//				if (CreateSolidFunctionsEnumUtils::getSolidPropertiesEnumByClassName(labelValue) == CreateSolidPropertiesEnum::DISTANCE)
//					if (!eCValue.IsNull())
//						extrusionReaderProperties->setThickness(eCValue.GetDouble());
//
//				solidsOperationProperties->setExtrusionReaderProperties(extrusionReaderProperties);
//			}
//			break;
//			case CreateSolidFunctionsEnum::EXTRUDE_ALONG:
//			{
//
//			}
//			break;
//			case CreateSolidFunctionsEnum::REVOLVE:
//			{
//				RevolveReaderProperties* revolveReaderProperties = new RevolveReaderProperties();
//
//				solidsOperationProperties->setRevolveReaderProperties(revolveReaderProperties);
//			}
//			break;
//			default:
//				break;
//		}
//		readerProperties.setCreateSolidsOperationProperties(solidsOperationProperties);
//	}*/
//}
//
//CreateSolidsOperationPropertiesReaderMapper::CreateSolidsOperationPropertiesReaderMapper()
//{
//}