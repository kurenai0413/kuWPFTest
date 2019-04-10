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

        //private kuOpenCVWrapperClass openCVWrapperObj = new kuOpenCVWrapperClass();

        public MainWindow()
        {
            InitializeComponent();
        }

        private void TestButton_Click(object sender, RoutedEventArgs e)
        {
            testCnt++;
            TestTextBlock.Text = "test num: " + testCnt.ToString();
        }
    }
}
