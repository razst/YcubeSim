﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace YcubeSimUDP
{
    public partial class Main : Form
    {

        UDPSocket server = new UDPSocket();
        UDPSocket client = new UDPSocket();


        public void updateList(string msg)
        {
            string mess = msg.Trim();
            listBox1.Items.Add(mess);
        }


        public Main()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            
        }

        private void button2_Click(object sender, EventArgs e)
        {
            client.Client(tbxIP.Text, int.Parse(tbxPort.Text));
        }

        private void button3_Click(object sender, EventArgs e)
        {
            client.Send(tbxSend.Text);
        }

        private void listView1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }

        private void button1_Click_1(object sender, EventArgs e)
        {
            server.Server(int.Parse(tbxPort.Text), this);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            listBox1.Items.Clear();
        }

        private void tbxIP_TextChanged(object sender, EventArgs e)
        {

        }

        private void Main_Load(object sender, EventArgs e)
        {

        }
    }
}
