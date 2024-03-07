using netCGAL;
Console.WriteLine("Started");

NetCGAL.CallMethod();

Mesh mesh = new()
{
	Points = [
		0.0f, 1.0f, 2.0f, 
		3.0f, 4.0f, 5.0f,
		6.0f, 7.0f, 8.0f],

	Indexes = [0, 1, 2],
};

int result = NetCGAL.Multi(mesh);

Console.WriteLine(result);

Console.WriteLine("Finished");
Console.ReadKey();