#pragma once

#include <fstream>
#include <string>
#include <source_location>
#include <vector>
#include <iostream>
#include <chrono>

using namespace std;

// TODO: Might not be the most optimal name, didn't think too long about it
struct ChannelConfig {
    vector<int> channels;
    vector<int> flags;
};

class CLog {
public:
    enum Channels
    {
        COUT,
        CERR,
        FILE
    };

    enum Flags
    {
        // Channel-specific flags for 'CERR'
        // ...
        // Channel-specific flags for 'FILE'
        // Note to self: DO NOT ALTER ORDER, new flags should be added last
        FORCEOVERWRITE,
    };

    inline static const ChannelConfig Log = { {COUT, FILE}, {} };
    inline static const ChannelConfig Error = { {CERR, FILE}, {} };

    /* Default Filename Override
    **/
    inline static string DefaultFilename = "log.txt";

    /// <summary>
    /// <para>Log to channel(s) by using a 'ChannelConfig'</para>
    /// <para>‎ </para>
    /// <para>QUICK USAGE:</para>
    /// <para>Log::ToChannels("Some message");</para>
    /// <para>‎</para>
    /// <para>Log an Error:</para>
    /// <para>Log::ToChannels("Some message", Log::Error);</para>
    /// </summary>
    static void ToChannels(string Message, ChannelConfig cc, const source_location Location = source_location::current()) {
        for (int channel : cc.channels) {
            auto now = chrono::system_clock::now();
            string formatted_time = std::format("{0:%F_%T}", now);

            // Available flags
            bool forceOverwrite = false;

            // Process flags
            for (int flag : cc.flags) {
                if (flag == FORCEOVERWRITE) forceOverwrite = true;
            }

            // TODO: Find a way to provide access for filename .. a 'packet' parameter wouldn't be nice, maybe.. would it?
            // Maybe not.
            string filename = DefaultFilename;

            switch (channel)
            {
            case COUT:
                cout << formatted_time <<
                    "\nFile: " <<
                    Location.file_name() << "(" <<
                    Location.line() << ":" <<
                    Location.column() << ") \n" <<
                    Location.function_name() << ": " <<
                    Message << endl << endl;
                break;
            case CERR:
                cerr << formatted_time <<
                    "\nFile: " <<
                    Location.file_name() << "(" <<
                    Location.line() << ":" <<
                    Location.column() << ") \n" <<
                    Location.function_name() << ": " <<
                    Message << endl << endl;
                break;
            case FILE:
                // Check if a file exists
                if (auto readFile = ifstream(filename) && !forceOverwrite)
                {
                    // File exists?: Append
                    ofstream outfile(filename, std::ios_base::app);
                    outfile << formatted_time <<
                        "\nFile: " <<
                        Location.file_name() << "(" <<
                        Location.line() << ":" <<
                        Location.column() << ") \n" <<
                        Location.function_name() << ": " <<
                        Message << endl << endl;
                    outfile.close();
                }
                else
                {
                    // File doesn't exist?: Overwrite
                    ofstream outfile(filename);
                    outfile << formatted_time <<
                        "\nFile: " <<
                        Location.file_name() << "(" <<
                        Location.line() << ":" <<
                        Location.column() << ") \n" <<
                        Location.function_name() << ": " <<
                        Message << endl << endl;
                    outfile.close();
                }
                break;
            default:
                break;
            }
        }
    }

    /// <summary>
    /// <para>Log to channel(s)</para>
    /// <para>‎ </para>
    /// <para>EXAMPLES</para>
    /// <para>Write to std::cerr and to a file</para>
    /// <para>Log::ToChannels("someMessage", { CERR, FILE });</para>
    /// <para>‎ </para>
    /// <para>Write to a custom file:</para>
    /// <para>Log::DefaultFilename = "myLogFile.txt";</para>
    /// <para>ToChannels("someMessage", { FILE });</para>
    /// </summary>
    /// 
    /// <param name="Message"></param>
    /// <param name="Channels"></param>
    /// <param name="Flags"></param>
    /// <param name="Location"></param>
    static void ToChannels(string Message, vector<int> Channels = {CERR, FILE}, vector<int> Flags = {}, const source_location Location = source_location::current()) {
        for (int channel : Channels) {
            auto now = chrono::system_clock::now();
            string formatted_time = std::format("{0:%F_%T}", now);
             

            // Available flags
            bool forceOverwrite = false;

            // Process flags
            for (int flag : Flags) {
                if (flag == FORCEOVERWRITE) forceOverwrite = true;
            }

            // TODO: Find a way to provide access for filename .. a 'packet' parameter wouldn't be nice, maybe.. would it?
            string filename = DefaultFilename;

            switch (channel)
            {
            case CERR:
                cerr << formatted_time <<
                "\nFile: " <<
                Location.file_name() << "(" <<
                Location.line() << ":" <<
                Location.column() << ") \n" <<
                Location.function_name() << ": " <<
                Message << endl << endl;
                break;
            case FILE:
                // Check if a file exists
                if (auto readFile = ifstream(filename) && !forceOverwrite)
                {
                    // File exists?: Append
                    ofstream outfile(filename, std::ios_base::app);
                    outfile << formatted_time <<
                        "\nFile: " <<
                        Location.file_name() << "(" <<
                        Location.line() << ":" <<
                        Location.column() << ") \n" <<
                        Location.function_name() << ": " <<
                        Message << endl << endl;
                    outfile.close();
                }
                else
                {
                    // File doesn't exist?: Overwrite
                    ofstream outfile(filename);
                    outfile << formatted_time <<
                        "\nFile: " <<
                        Location.file_name() << "(" <<
                        Location.line() << ":" <<
                        Location.column() << ") \n" <<
                        Location.function_name() << ": " <<
                        Message << endl << endl;
                    outfile.close();
                }
                break;
            default:
                break;
            }
        }
    }
};