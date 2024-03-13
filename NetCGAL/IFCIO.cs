using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
//using Xbim.Ifc;
//using Xbim.Ifc4.Interfaces;
//using Xbim.Ifc4x3.GeometricModelResource;

namespace NetCGAL
{
	public class IFCIO
	{
		public void Load(string fileName)
		{
			//var editor = new XbimEditorCredentials
			//{
			//	ApplicationDevelopersName = "You",
			//	ApplicationFullName = "Your app",
			//	ApplicationIdentifier = "Your app ID",
			//	ApplicationVersion = "4.0",
			//	//your user
			//	EditorsFamilyName = "Santini Aichel",
			//	EditorsGivenName = "Johann Blasius",
			//	EditorsOrganisationName = "Independent Architecture"
			//};

			//using (var model = IfcStore.Open(fileName, editor))
			//{
			//	using (var txn = model.BeginTransaction("Quick start transaction"))
			//	{
			//		//get all walls in the model
			//		var walls = model.Instances.OfType<IIfcWall>();

			//		//iterate over all the walls and change them
			//		foreach (var wall in walls)
			//		{
			//			wall.Name = "Iterated wall: " + wall.Name;
			//			string qq = wall.Name;
			//			wall.Name = qq.Replace("Iterated wall: ", "");
			//		}
			//		txn.Commit();
			//	}

			//	model.SaveAs(fileName);
			//}
		}
	}
}
