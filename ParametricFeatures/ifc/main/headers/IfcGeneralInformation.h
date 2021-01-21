#pragma once

/**
 * @file IfcGeneralInformation.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <ctime>
#include "../../../stdafx.h"


namespace Ifc
{
	namespace Main
	{
		/**
		 * @brief Ifc General Information Class that generate the file (IfcHierarchyHelper) and 
		 * collects the additional information necessary to complete the ifc file:
		 * IfcGeometricRepresentationContext, IfcOwnerHistory, IfcObjectPlacement, IfcHierarchyHelper
		 * 
		 */
		class IfcGeneralInformation
		{
		public:
			static IfcGeneralInformation* getInstance()
			{
				call_once(initInstanceFlag, &IfcGeneralInformation::initIfcGeneralInformation);
				return _IfcGeneralInformation;
			};

			static void resetInstance()
			{
				delete _IfcGeneralInformation;
				_IfcGeneralInformation = new IfcGeneralInformation();
			}

			/**
			 * @brief Set the User Actor Name object
			 * 
			 * @param name 
			 */
			void setActorName(string name);

			/**
			 * @brief Set the User Actor Sur Name object
			 * 
			 * @param sName 
			 */
			void setActorSurName(string sName);

			/**
			 * @brief Set the User Actor Email object
			 * 
			 * @param mail 
			 */
			void setActorEmail(string mail);

			/**
			 * @brief Set the User Actor Role object
			 * 
			 * @param role 
			 */
			void setActorRole(Ifc4::IfcRoleEnum::Value role);

			/**
			 * @brief Build the General Info for the Ifc file
			 * 
			 */
			void buildIfcGeneralInfo();

			/**
			 * @brief Get the User Actor Name object
			 * 
			 * @return string 
			 */
			string getActorName();

			/**
			 * @brief Get the User Actor Sur Name object
			 * 
			 * @return string 
			 */
			string getActorSurName();

			/**
			 * @brief Get the User Actor Email object
			 * 
			 * @return string 
			 */
			string getActorEmail();

			/**
			 * @brief Set the Default Values of the class
			 * 
			 * @return true 
			 * @return false 
			 */
			bool setDefaultValues();

			/**
			 * @brief Get the Ifc Hierarchy Helper object
			 * 
			 * @return IfcHierarchyHelper<Ifc4>& 
			 */
			IfcHierarchyHelper<Ifc4>& getIfcHierarchyHelper();

			/**
			 * @brief Get the Geometric Context object
			 * 
			 * @return Ifc4::IfcGeometricRepresentationContext* 
			 */
			Ifc4::IfcGeometricRepresentationContext* getGeometricContext();

			/**
			 * @brief Get the Owner History object
			 * 
			 * @return Ifc4::IfcOwnerHistory* 
			 */
			Ifc4::IfcOwnerHistory* getOwnerHistory();

			/**
			 * @brief Get the Object Placement object
			 * 
			 * @return Ifc4::IfcObjectPlacement* 
			 */
			Ifc4::IfcObjectPlacement* getObjectPlacement();
		private:
			IfcGeneralInformation();

			static IfcGeneralInformation* _IfcGeneralInformation;
			static once_flag initInstanceFlag;
			static void initIfcGeneralInformation()
			{
				_IfcGeneralInformation = new IfcGeneralInformation();
			}

			/**
			 * @brief Get the Developer Role object
			 * 
			 * @return IfcTemplatedEntityList<Ifc4::IfcActorRole>* 
			 */
			IfcTemplatedEntityList<Ifc4::IfcActorRole>* getDeveloperRole();

			/**
			 * @brief Get the User Role object
			 * 
			 * @return IfcTemplatedEntityList<Ifc4::IfcActorRole>* 
			 */
			IfcTemplatedEntityList<Ifc4::IfcActorRole>* getUserRole();

			/**
			 * @brief Get the Representation Context object
			 * 
			 * @return IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>* 
			 */
			IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>* getRepresentationContext();

			/**
			 * @brief Get the Address object
			 * 
			 * @return IfcTemplatedEntityList<Ifc4::IfcAddress>* 
			 */
			IfcTemplatedEntityList<Ifc4::IfcAddress>* getAddress();

			/**
			 * @brief Get the Unit Assignment object
			 * 
			 * @return Ifc4::IfcUnitAssignment* 
			 */
			Ifc4::IfcUnitAssignment* getUnitAssignment();

			WString _orgaization, _fullName;
			string _actorName;
			string _actorSurName;
			string _actorEmail;
			Ifc4::IfcRoleEnum::Value _actorRole = Ifc4::IfcRoleEnum::Value(0);
			Ifc4::IfcGeometricRepresentationContext* _geometricContext;
			Ifc4::IfcOwnerHistory* _ownerHistory;
			Ifc4::IfcObjectPlacement* _objectPlacement;
			IfcHierarchyHelper<Ifc4>* _file = 0;
		};
	}
}