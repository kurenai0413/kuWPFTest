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
using System.Runtime.InteropServices;
using System.Threading;
using kuCLRWrapper;

namespace kuWPFTest
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        bool    IsCameraOpened = false;
        IntPtr  PictureBoxHandle;
        Thread  CameraThread;

        kuOpenCVCameraClassWrapper wrapperObj = new kuOpenCVCameraClassWrapper();
        
        public MainWindow()
        {
            InitializeComponent();

            PictureBoxHandle = PictureBox.Handle;
            wrapperObj.kuCreateWindow("TestView", (int)PictureBoxHandle, 1600, 900);
        }

        ~MainWindow()
        {

        }

        private void OpenCameraButton_Click(object sender, RoutedEventArgs e)
        {            
            if (!IsCameraOpened)
            {
                IsCameraOpened = wrapperObj.kuStartCamera(0);

                if (IsCameraOpened)
                {
                    CameraStatusText.Text = "Camera is opened.";

                    CameraThread = new Thread(CameraThreadFun);
                    CameraThread.Start();
                }   
            }
        }

        private void CloseCameraButton_Click(object sender, RoutedEventArgs e)
        {
            if (IsCameraOpened)
            {
                IsCameraOpened = false;
            }
        }

        private void CameraThreadFun()
        {
            while (IsCameraOpened)
            {
                bool camFrameFlag = wrapperObj.kuGetCamframe();

                if (camFrameFlag)
                {
                    wrapperObj.kuShowImage();
                }
            }
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            IsCameraOpened = false;
            wrapperObj.kuCloseCamera();
            wrapperObj.kuDestroyCurrentWindow();
        }

        private void Window_KeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Escape)
            {
                Application.Current.Shutdown();
            }
        }

        private void ProcessingButton_Click(object sender, RoutedEventArgs e)
        {

        }

        private void SetColorButton1_Click(object sender, RoutedEventArgs e)
        {

        }

        private void SetColorButton2_Click(object sender, RoutedEventArgs e)
        {

        }

        private void SetColorButton3_Click(object sender, RoutedEventArgs e)
        {

        }

        private void SetColorButton4_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
