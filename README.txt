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
