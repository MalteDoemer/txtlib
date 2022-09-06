

using System.Net.Sockets;

enum Direction : sbyte
{
    Forward = -1,
    Backward = 1,
}

struct MotorCommand
{
    Direction leftDirection;
    Direction rightDirection;
    uint leftDistance;
    uint rightDistance;

    public MotorCommand(Direction leftDirection, Direction rightDirection, uint leftDistance, uint rightDistance)
    {
        this.leftDirection = leftDirection;
        this.rightDirection = rightDirection;
        this.leftDistance = leftDistance;
        this.rightDistance = rightDistance;
    }

    public byte[] GetBytes()
    {
        var bytes = new List<byte>();

        bytes.Add((byte)leftDirection);
        bytes.Add((byte)rightDirection);

        // reserved
        bytes.Add(0);
        bytes.Add(0);

        bytes.AddRange(BitConverter.GetBytes(leftDistance));
        bytes.AddRange(BitConverter.GetBytes(rightDistance));

        return bytes.ToArray();
    }

}

class Program
{
    static void Main()
    {
        var port = 10000;
        var server = "192.168.7.2";

        var cmd = new MotorCommand(Direction.Forward, Direction.Forward, 100, 100);

        using (var client = new TcpClient(server, port))
        using (var stream = client.GetStream())
        {
            var data = cmd.GetBytes();
            System.Console.WriteLine(data.Length);
            stream.Write(data, 0, data.Length);
        }
    }
}