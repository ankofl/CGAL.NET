//using Grpc.Core;
using System;
using System.Collections.Generic;
using System.IO.Pipes;
using System.Linq;
using System.Runtime.Serialization.Formatters.Binary;
using System.Text;
using System.Threading.Tasks;

namespace NetCGAL
{

	//class MeshServiceImpl : MeshService.MeshServiceBase
	//{
	//	public override Task<MeshStruct> SendMesh(MeshStruct request, ServerCallContext context)
	//	{
	//		// Ваша логика обработки структуры MeshStruct здесь

	//		// Пример: просто возвращаем полученную структуру обратно клиенту
	//		return Task.FromResult(request);
	//	}
	//}

	class Program
	{
		const int Port = 50051;

		static void Main(string[] args)
		{
			//Server server = new Server
			//{
			//	//Services = { MeshService.BindService(new MeshServiceImpl()) },
			//	//Ports = { new ServerPort("localhost", Port, ServerCredentials.Insecure) }
			//};
			//server.Start();

			//Console.WriteLine("Server listening on port " + Port);
			//Console.WriteLine("Press any key to stop the server...");
			//Console.ReadKey();

			//server.ShutdownAsync().Wait();
		}
	}

	public static class PipesIO
	{
		public static byte[] Input(string pipeName)
		{
			byte[] data = null;

			using (NamedPipeClientStream clientStream = new(".", pipeName, PipeDirection.In))
			{
				// Connect to the pipe or wait until the pipe is available.
				clientStream.Connect();
			}

			return data;
		}

		public static void Output(string pipeName, byte[] data)
		{
			using (NamedPipeServerStream serverStream = new NamedPipeServerStream(pipeName, PipeDirection.Out))
			{
				serverStream.WaitForConnection();
			}
		}
	}
}
