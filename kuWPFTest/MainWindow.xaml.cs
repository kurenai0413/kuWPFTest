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
        Thread  ProcessingThread;

        int     m_HairHueValue;

        bool    m_isHairMaskGenerated = false;

        bool    SingleImageButtonClicked = false;

        kuOpenCVCameraClassWrapper wrapperObj = new kuOpenCVCameraClassWrapper();
        
        public MainWindow()
        {
            InitializeComponent();

            wrapperObj.kuLoadDlibModels();

            PictureBoxHandle = PictureBox.Handle;
            wrapperObj.kuCreateWindow("TestView", (int)PictureBoxHandle, 1600, 900);

            m_HairHueValue = 105; // Default #BE9C7A
        }

        ~MainWindow()
        {

        }

        private void StartCameraFun()
        {
            IsCameraOpened = wrapperObj.kuStartCamera(0);
            
            if (IsCameraOpened)
            {
                CameraStatusText.Text = "Camera is opened.";

                CameraThread = new Thread(CameraThreadFun);
                CameraThread.Start();

                m_isHairMaskGenerated = false;
            }
        }

        private void OpenCameraButton_Click(object sender, RoutedEventArgs e)
        {            
            if (!IsCameraOpened)
            {
                StartCameraFun();
            }
        }

        private void CloseCameraButton_Click(object sender, RoutedEventArgs e)
        {
            if (IsCameraOpened)
            {
                IsCameraOpened = false;

                wrapperObj.kuCloseCamera();
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

        private void FrameProcessingFun()
        {
            wrapperObj.kuSetHairHueColor(m_HairHueValue);
            m_isHairMaskGenerated = wrapperObj.kuGenerateHairMask();

            if (m_isHairMaskGenerated)
            {
                MessageBox.Show("Face is detected");
            }
            else
            {
                MessageBox.Show("Face is not detected");
                CameraStatusText.Text = "Face is not detected.";

                //StartCameraFun();
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
            if (IsCameraOpened)
            {
                IsCameraOpened = false;

                wrapperObj.kuGetProcessingFrame();
                wrapperObj.kuCloseCamera();
                wrapperObj.kuShowProcessedImage();

                //ProcessingThread = new Thread(FrameProcessingFun);
                //ProcessingThread.Start();
                
                wrapperObj.kuSetHairHueColor(m_HairHueValue);

                CameraStatusText.Text = "Start processing.";
                //MessageBox.Show("Start processing");

                m_isHairMaskGenerated = wrapperObj.kuGenerateHairMask();

                if (m_isHairMaskGenerated)
                {
                    wrapperObj.kuChangeHairColor();
                }
                else
                {
                    MessageBox.Show("Face is not detected");
                    CameraStatusText.Text = "Face is not detected.";

                    StartCameraFun();
                }

                CameraStatusText.Text = "Processing done." + m_isHairMaskGenerated;
            }
        }

        private void SetColorButton1_Click(object sender, RoutedEventArgs e)
        {
            if (m_isHairMaskGenerated)
            {
                m_HairHueValue = 105; // BE9C7A
                wrapperObj.kuSetHairHueColor(m_HairHueValue);
                wrapperObj.kuChangeHairColor();
            }
        }

        private void SetColorButton2_Click(object sender, RoutedEventArgs e)
        {
            if (m_isHairMaskGenerated)
            {
                m_HairHueValue = 115; // CA3A1C
                wrapperObj.kuSetHairHueColor(m_HairHueValue);
                wrapperObj.kuChangeHairColor();
            }
        }

        private void SetColorButton3_Click(object sender, RoutedEventArgs e)
        {
            if (m_isHairMaskGenerated)
            {
                m_HairHueValue = 120; // A80001
                wrapperObj.kuSetHairHueColor(m_HairHueValue);
                wrapperObj.kuChangeHairColor();
            }
        }

        private void SetColorButton4_Click(object sender, RoutedEventArgs e)
        {
            if (m_isHairMaskGenerated)
            {
                m_HairHueValue = 125; // A62C42
                wrapperObj.kuSetHairHueColor(m_HairHueValue);
                wrapperObj.kuChangeHairColor();
            }
        }

        private void CloseAppButton_Click(object sender, RoutedEventArgs e)
        {
            Application.Current.Shutdown();
        }

        private void ProcessingSingleImageButton_Click(object sender, RoutedEventArgs e)
        {
            ProcessingSingleImageButton.IsEnabled = false;

            if (IsCameraOpened)
            {
                IsCameraOpened = false;
            
                wrapperObj.kuCloseCamera();
            }
            
            wrapperObj.kuLoadProcessingImage("UniColor_Peggy_A2.jpg");
            wrapperObj.kuShowProcessedImage();
            
            IsCameraOpened = false;
            
            wrapperObj.kuSetHairHueColor(m_HairHueValue);
            m_isHairMaskGenerated = wrapperObj.kuGenerateHairMask();
            
            if (m_isHairMaskGenerated)
            {
                wrapperObj.kuChangeHairColor();
            }

            ProcessingSingleImageButton.IsEnabled = true;
        }
    }
}
