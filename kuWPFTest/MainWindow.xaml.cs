using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using kuOpenCVWrapper;
using System.Runtime.InteropServices;

namespace kuWPFTest
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        int testCnt = 0;

        kuOpenCVWrapperClass wrapperObj = new kuOpenCVWrapperClass();

        IntPtr m_PictureBoxHandle;

        public MainWindow()
        {
            InitializeComponent();
        }

        ~MainWindow()
        {

        }

        private void TestButton_Click(object sender, RoutedEventArgs e)
        {
            wrapperObj.kuLoadImage("WIN_20190412_11_54_22_Pro.jpg");

            IntPtr hwnd = PictureBox.Handle;

            //wrapperObj.kuStartCamera(0);
            wrapperObj.kuCreateWindow("TestView", (int)hwnd);
            wrapperObj.kuShowImage();

            //TestTextBlock.Text = "Camera started.";

            //while (true)
            //{
            //    bool camFrameFlag = wrapperObj.kuGetCamframe();

            //    if (camFrameFlag)
            //    {
            //        wrapperObj.kuShowImage();
            //    }
            //}

            //testCnt++;

        }

        private void Window_Closed(object sender, EventArgs e)
        {
            wrapperObj.kuCloseCamera();
            wrapperObj.kuDestroyCurrentWindow();
        }
    }
}
