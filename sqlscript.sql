/**
	the sql script to create the DB
*/
/**
the old schema
BEGIN TRANSACTION;
CREATE TABLE "channel_table" ("channel_id" INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL , "channel_name" VARCHAR NOT NULL , "channel_link" VARCHAR, "channel_desc" VARCHAR);
INSERT INTO "channel_table" VALUES(6,'code project c++','http://www.codeproject.com/webservices/articlerss.aspx?cat=2','description');
INSERT INTO "channel_table" VALUES(7,'f55','http://feeds.feedburner.com/f055','desc2');
COMMIT;

*/

-- the channel table : a table to hold the feed file info
BEGIN TRANSACTION;
create table channel_table (
	channel_id integer primary key AUTOINCREMENT,
	channel_name varchar(100),
	channel_link varchar(200) not null unique,
	channel_desc varchar(4000),
	channel_lang varchar(10)
	);

COMMIT;

-- the item_table for storing the news article
BEGIN TRANSACTION;
create table item_table (
item_id integer primary key AUTOINCREMENT,
						 	itm_title varchar(100),
							item_link varchar(200) not null,
							channel_desc varchar(4000),
							channel_lang varchar(10)
							);							
COMMIT;


