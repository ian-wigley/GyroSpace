//////////////////////////////////////////////////
//
// Gyrospace
//
// Written by Ian Wigley
//
///////////////////////////////////////////////////

// C# Class to handle the HighScores, Temporary Storage access (Async Loading & Saving)

using System;
using System.Collections.Generic;
using System.Threading;
using Windows.System;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Navigation;
using Windows.Storage;
using Windows.UI.Notifications;
using Windows.Data.Xml.Dom;
using Windows.ApplicationModel.DataTransfer;

namespace MenuComponents.Storage
{
    public sealed class TemporaryStorageAccess
    {
        Grid m_inputName;
        String m_scoreList;

        TextBlock m_score1;
        TextBlock m_score2;
        TextBlock m_score3;
        TextBlock m_score4;
        TextBlock m_score5;

        int m_count;
        int m_score;

        int[] m_highScores = { 5000, 4000, 3000, 2000, 1000 };
        string[] m_highNames = { "ABC", "DEF", "GHI", "JKL", "MNO" };

        StorageFolder m_roamingFolder = null;
        const string m_filename = "HighScores.txt";
        string m_scores = "";

        Button m_button;
        TextBox m_textBox;

        /// <summary>
        /// Constructor
        /// </summary>
        public TemporaryStorageAccess(TextBlock _score1, TextBlock _score2, TextBlock _score3, TextBlock _score4, TextBlock _score5, Grid _inputName)
        {
            m_score1 = _score1;
            m_score2 = _score2;
            m_score3 = _score3;
            m_score4 = _score4;
            m_score5 = _score5;

            m_inputName = _inputName;

            // Create a new TextBox & Add it to the Grid
            m_textBox = new TextBox();
            m_textBox.Width = 20;
            m_textBox.MaxLength = 3;
            m_textBox.MaxHeight = 1;
            m_inputName.Children.Add(m_textBox);

            // Create a new Button & Add it to the Grid
            m_button = new Button();
            m_button.Content = "Close";
            m_button.HorizontalAlignment = HorizontalAlignment.Center;
            m_button.VerticalAlignment = VerticalAlignment.Bottom;
            Thickness marginThickness = m_button.Margin;
            marginThickness = new Thickness(114, 0, 113, 10);
            m_inputName.Children.Add(m_button);
            
            // Try & load the scores from the Roaming Folder
            ReadScores();

            m_button.Click += new RoutedEventHandler(delegate(Object o, RoutedEventArgs e) { this.SortHighScores(o, e); });
        }

        // Write the highscore out to a file
        public async void WriteScores()
        {
            m_roamingFolder = ApplicationData.Current.RoamingFolder;

            for (int i = 0; i < m_highScores.Length; i++)
            {
                m_scores += m_highScores[i] + "," + m_highNames[i] + ",";
            }
            StorageFile sampleFile = await m_roamingFolder.CreateFileAsync(m_filename, CreationCollisionOption.ReplaceExisting);
            await FileIO.WriteTextAsync(sampleFile, m_scores);
        }

        // Read the highscores from the file
        public async void ReadScores()
        {
            m_roamingFolder = ApplicationData.Current.RoamingFolder;
            try
            {
                StorageFile sampleFile = await m_roamingFolder.GetFileAsync(m_filename);
                m_scoreList = await FileIO.ReadTextAsync(sampleFile);

                string[] _splitHiScores = m_scoreList.Split(',');

                int j = 0;
                for (int i = 0; i < m_highScores.Length; i++, j+=2)
                {
                    int.TryParse(_splitHiScores[j], out m_highScores[i]);
                    m_highNames[i] = _splitHiScores[j + 1];
                    m_scores += m_highScores[i] + "," + m_highNames[i] + ",";
                }
                UpdateGrid();

                // Allow the High-Scores to be shared via a contract
                ShareScores();
            }
            catch (Exception)
            {
                // File not found... Use the original Payload values
            }
        }

        // Method to use the basic timer to count down 3 secons 
        public bool Delay(float _total, float _Delta)
        {
            if (_total > 2)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

        // Method to update the High-Score Table
        public void UpdateScores(int _score)
        {
            bool _scoreFound = false;
            for (int i = 0; i < m_highScores.Length; i++)
            {
                if (_score >= m_highScores[i] && !_scoreFound)
                {
                    _scoreFound = true;
                    InputName(i, _score);
                }
            }
        }

        // Method to update the High Scores on the Grid
        private void UpdateGrid()
        {
            m_score1.Text = m_highScores[0] + " " + m_highNames[0];
            m_score2.Text = m_highScores[1] + " " + m_highNames[1];
            m_score3.Text = m_highScores[2] + " " + m_highNames[2];
            m_score4.Text = m_highScores[3] + " " + m_highNames[3];
            m_score5.Text = m_highScores[4] + " " + m_highNames[4];
        }

        // Method to Display a Grid to allow you to input your name
        private void InputName(int _count, int _score)
        {
            m_inputName.Visibility = Visibility.Visible;
            m_score = _score;
            m_count = _count;
        }

        // Method to update the Live Tile with the latest Score information
        private void UpdateLiveTile()
        {
            Windows.Globalization.DateTimeFormatting.DateTimeFormatter _formatter = new Windows.Globalization.DateTimeFormatting.DateTimeFormatter("longtime");
            string _timePlayed = _formatter.Format(DateTime.Now).ToString();

            // Get tile template - small tile
            XmlDocument tileXml = TileUpdateManager.GetTemplateContent(TileTemplateType.TileSquareText04);

            // Set tile info
            XmlNodeList tileText = tileXml.GetElementsByTagName("text");
            tileText[0].InnerText = "Last Played: " + _timePlayed;
             
            // Wide tile
            XmlDocument wideTileXml = TileUpdateManager.GetTemplateContent(TileTemplateType.TileWideImageAndText02);
            XmlNodeList wideTileText = wideTileXml.GetElementsByTagName("text");
            wideTileText[0].InnerText = "Last Played: " + _timePlayed;
            wideTileText[1].InnerText = "Highest Score: " + m_highScores[0].ToString();

            // Add the wide tile to the square tiles payload by retrieving the binding element
            IXmlNode node = tileXml.ImportNode(wideTileXml.GetElementsByTagName("binding").Item(0), true);
            tileXml.GetElementsByTagName("visual").Item(0).AppendChild(node);
            
            // Apply the tile
            TileNotification tileNotification = new TileNotification(tileXml);
            
            // Update the app tile
            TileUpdateManager.CreateTileUpdaterForApplication().Update(tileNotification);
        }
        
        // Method to share the latest Score information using a Contract
        private void ShareScores()
        {
            //Declare a DataTransferManager object:
            DataTransferManager _dataTransferManager = null;
            //Assign an event handler:
            _dataTransferManager = DataTransferManager.GetForCurrentView();
            _dataTransferManager.DataRequested += new Windows.Foundation.TypedEventHandler<DataTransferManager, DataRequestedEventArgs>(this.ShareLinkHandler);
        }

        // Share Contract event Handler
         void ShareLinkHandler(DataTransferManager sender, DataRequestedEventArgs e)
        {
            DataRequest request = e.Request;
            request.Data.Properties.Title = "GyroSpace";
		    request.Data.Properties.Description = "Latest High Scores";
		    request.Data.SetText(m_scores);
        }

        // Method to sort the order of the high scores
        private void SortHighScores(Object o, RoutedEventArgs e)
        {
            // Move the array contents down  
            for (int j = m_highScores.Length - 1; j != m_count; j--)
            {
                int m_tempScore = m_highScores[j - 1];
                m_highScores[j] = m_tempScore;

                string m_tempName = m_highNames[j - 1];
                m_highNames[j] = m_tempName;
            }
            
            // Add the new Score & Name
            m_highScores[m_count] = m_score;
            m_highNames[m_count] = m_textBox.Text;

            m_inputName.Visibility = Visibility.Collapsed;
            m_textBox.Text = "";

            // Write out the updated scores
            WriteScores();
            UpdateGrid();
            UpdateLiveTile();
        }
    }
}






