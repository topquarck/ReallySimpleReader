the status of the project: Sat 30-5-2009
***********************************************
Main/Central Class: ReallySimpleReader

                ReallySimpleReader ------> RSRMainWindow(UI)
                  |     |         |
                  |     |         |
    HttpDownloader(Http)|    DBManager(db)
                        |
                    XmlParser(Dom)
====================================================
A New proposal : create a sub-central

                ReallySimpleReader ------> RSRMainWindow(UI)
                  |     |         |
                  |     |         |
    HttpDownloader(Http)|          DBManager(db)
                        |                   |
                    XmlParser(Dom)          |
                                        DBConnector(db)
****************
A New proposal : change in the design: create a nee class
            to handle the file saving < saving the feed url in files>
            and put the downloader under the parser

                ReallySimpleReader <------ RSRMainWindow(UI)
                  |     |         |
                  |     |         |
             FeedStore  |
                    HttpDownloader(Http)
                        |
                        |
                     XmlParser(Dom)
