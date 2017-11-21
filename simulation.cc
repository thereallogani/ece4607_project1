#include "ns3/core-module.h"
#include "ns3/netanim-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"


using namespace ns3;

NS_LOG_COMPONENT_DEFINE("ECE4607-Project1");
int NUM_NODES = 7;


int main (int argc, char *argv[])
{
    CommandLine cmd;
    cmd.Parse(argc, argv);

    Time::SetResolution(Time::NS);
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    NodeContainer nodes;
    nodes.Create(NUM_NODES);

    InternetStackHelper stack;
    stack.Install(nodes);

    PointToPointHelper p2p_0;
    p2p_0.SetDeviceAttribute("DataRate", StringValue("20Mbps"));
    p2p_0.SetChannelAttribute("Delay", StringValue("2ms"));

    PointToPointHelper p2p_1;
    p2p_1.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    p2p_1.SetChannelAttribute("Delay", StringValue("5ms"));

    PointToPointHelper p2p_2;
    p2p_2.SetDeviceAttribute("DataRate", StringValue("20Mbps"));
    p2p_2.SetChannelAttribute("Delay", StringValue("40ms"));

    PointToPointHelper p2p_3;
    p2p_3.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    p2p_3.SetChannelAttribute("Delay", StringValue("45ms"));

    PointToPointHelper p2p_4;
    p2p_4.SetDeviceAttribute("DataRate", StringValue("20Mbps"));
    p2p_4.SetChannelAttribute("Delay", StringValue("3ms"));

    PointToPointHelper p2p_5;
    p2p_5.SetDeviceAttribute("DataRate", StringValue("10Mbps"));
    p2p_5.SetChannelAttribute("Delay", StringValue("5ms"));

    // Declare helpers
    Ipv4AddressHelper address;
    NetDeviceContainer devices;
    Ipv4InterfaceContainer interfaces;


    // set up nodes 0, 1, 2 point to point
    address.SetBase("10.1.0.0", "255.255.255.0");
    devices = p2p_0.Install(nodes.Get(0), nodes.Get(2));
    interfaces = address.Assign(devices);
    devices = p2p_1.Install(nodes.Get(1), nodes.Get(2));
    interfaces = address.Assign(devices);

    // set up nodes 2, 3 point to point
    address.SetBase("10.1.1.0", "255.255.255.0");
    devices = p2p_2.Install(nodes.Get(2), nodes.Get(3));
    interfaces = address.Assign(devices);

    // set up nodes 3, 4 point to point
    address.SetBase("10.1.2.0", "255.255.255.0");
    devices = p2p_3.Install(nodes.Get(3), nodes.Get(4));
    interfaces = address.Assign(devices);

    // set up nodes 4, 5, 6 point to point
    address.SetBase("10.1.3.0", "255.255.255.0");
    devices = p2p_4.Install(nodes.Get(4), nodes.Get(5));
    interfaces = address.Assign(devices);
    devices = p2p_5.Install(nodes.Get(4), nodes.Get(6));
    interfaces = address.Assign(devices);

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    UdpEchoServerHelper echoServer(9);

    ApplicationContainer serverApps = echoServer.Install(nodes.Get(6));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(interfaces.GetAddress(1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(1));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
    clientApps.Start(Seconds (2.0));
    clientApps.Stop(Seconds (100.0));

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}
