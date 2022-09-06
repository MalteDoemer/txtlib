using System.Net.Sockets;

enum Direction : sbyte
{
    Forward = -1,
    Backward = 1,
}

struct MotorCommand
{
    public Direction leftDirection { get; set; }
    public Direction rightDirection { get; set; }
    public uint leftDistance { get; set; }
    public uint rightDistance { get; set; }

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
    private MotorCommand leftCmd;
    private MotorCommand forwardCmd;
    private MotorCommand backCmd;
    private MotorCommand rightCmd;


    private TcpClient client;
    private NetworkStream stream;

    private bool done = false;

    private Program(string server, int port)
    {
        client = new TcpClient(server, port);
        stream = client.GetStream();

        forwardCmd = new MotorCommand
        {
            leftDirection = Direction.Forward,
            rightDirection = Direction.Forward,
            leftDistance = 100,
            rightDistance = 100,
        };

        leftCmd = new MotorCommand
        {
            leftDirection = Direction.Backward,
            rightDirection = Direction.Forward,
            leftDistance = 20,
            rightDistance = 20,
        };

        rightCmd = new MotorCommand
        {
            leftDirection = Direction.Forward,
            rightDirection = Direction.Backward,
            leftDistance = 20,
            rightDistance = 20,
        };


        backCmd = new MotorCommand
        {
            leftDirection = Direction.Backward,
            rightDirection = Direction.Backward,
            leftDistance = 100,
            rightDistance = 100,
        };

    }


    private void Run()
    {
        while (!done)
        {
            var key = Console.ReadKey(true);
            HandleKey(key);
        }
    }

    private void HandleKey(ConsoleKeyInfo key)
    {
        switch (key.Key)
        {
            case ConsoleKey.A:
                SendCommand(leftCmd); break;
            case ConsoleKey.W:
                SendCommand(forwardCmd); break;
            case ConsoleKey.S:
                SendCommand(backCmd); break;
            case ConsoleKey.D:
                SendCommand(rightCmd); break;

            case ConsoleKey.Escape:
                done = true; break;
        }
    }

    private void SendCommand(MotorCommand command)
    {
        var data = command.GetBytes();
        stream.Write(data, 0, data.Length);
    }


    static void Main()
    {
        var prog = new Program("192.168.8.2", 10000);
        prog.Run();
    }
}