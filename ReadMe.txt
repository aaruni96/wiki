Project Wiki.

When you do stuff, update the changelog!

Things it is expected to do :
	Make new files.			#done						#super waala done
	Read old files.			#done						#super waala done
	Overwrite old files.		#done						#integrated into module 1
	Provide search feature.		#done						#plain old done
	Provide index feature.		#nix specific implementation done

	[Provide user login]		#done(new)
	[Provide user register]		#done(new)
	[Provide logs]									#will be integrated into each module
	[Password hash]			#done
	
Miscellaneous Things related to the Wiki :
	Documentation.
		ReadMe: 
			What is it?
			Why use it?
			How to use it?
			Name/version number.
		Internal comments.
	Content.
		Make sample content.
			May copy from wikipedia.
			Include acknowledgments.
			Don't copy from proprietary sources.
	Testing.
		Test it under against various parameters for software stability, response speed, robustness.
			Should never abruptly terminate. Must always write a log file on error. Must display a user friendly error.
	Porting.
		Must port to blue-screen TC++ in school.
			Must ensure not to write too much *nix specific code.
			All code must run in target computer dos prompt.
			Code should also run independently of target computer. Will need to distribute and test.
	Packaging.
		An installer script and/or an installer package may be provided.
			Make sure all the paths are as expected by the program (compiled binary).
			
Directory Structure :
	Code :
		modules:
			Folder holds all modules for the program compilation. only needed in pre-compilation stage. May package as source.
			Edit : No more modules. Just one huge file.
		content:
			Folder holds all runtime content, except the binary file. Will contain subfolders.
			Logs:
				Holds all logs. Contains user logs and error logs as two separate files, upto inf size. (Be careful here, don't want QIRC situational logs).
				Edit : merged user logs and error logs. Have one huge debug log now. All the best to anyone trying to debug it!
			Data:
				Holds all data, along with an index file.
			User:
				Holds user login and data in two separate files. (or in concurrent lines in same file?)
				Edit : two files it is.
				
Timeline/Changelog:

	16 August 2014
		Formally started the project. Wrote this file. Wrote write module, read module, index module(nix), search module. None of today's work will go into the final form as it is right now. I have functionality, will need to integrate everything, add logging functionality, and make things cleaner. Added pwd hash to expected functions.
		
	27 August 2014
		Forgot that the file also has a changelog. But doesn't matter. Rewrote the write module, edited the read module, wrote a register module. Edited the file to remind me to update the changelog. Need to integrate logging into the modules.
		
	30 August 2014
		Wrote the login module. Now that all individual modules are done, need to write the main module, to integrate everything and provide internal logging. Other than that, still need to write the internal documentation, the external documentation and get my content. Also need to write some installer scripts to make the requisite files and folders for the wiki to work.
		Wrote main.cpp. Done with logging feature too. Just need to make it "shippable now".
		Added internal documentation to the code.
	31 August 2014
		00:12:10 IST. Still adding finesse to the main.cpp file. Done logging. Done file paths. Done some basic level debugging. I think I may now freeze the main.cpp file.
		Uploaded main.cpp to github. Now, I need sleep.
	2 September 2014
		Added another function to main.cpp, to print contents of index file. Most functions fail if the directory structure isn't as expected. Need to either manually check for those, or think of something else.
		Wrote "WhatIs" document.
		Wrote "Manual" document.
