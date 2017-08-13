#include "matchhistory.h"
#include <iostream>
#include <algorithm>
#include <QSettings>

// See matchhistory.h for descriptions of each method.

// Default ctor
MatchHistory::MatchHistory()
{
    QSettings settings;
    QString temp;
    int size = settings.beginReadArray( "history" );
    for ( int i = 0; i < size; i++ ) {
        settings.setArrayIndex(i);
        temp = settings.value( "name" ).toString();
        history.push_back( temp );
    }
    settings.endArray();
}

// Determines if a match has been made.
bool MatchHistory::is_match( QVector<QString> curr )
{
    for ( QString i: curr )
        if ( std::binary_search( history.begin(), history.end(), i ))
            return true;

    // no match found.
    return false;
}



// Sets the top-most match for testing against next match.
void MatchHistory::set_history(QVector<QString> top)
{
    // Make sure top has values.
    if (top.empty())
        return ;

    for ( QString name: top )
        history.push_front(name);
    curr_top = top;
    // Keep history at 5 or less name stacks.
    if ( history.size() >= 5*top.size() )
        history.resize(5*top.size());
    save_history();

    return ;
}


// adjust matches to get rid of certain names.
void MatchHistory::adjust_matches(QVector<QString> to_remove)
{

}



// Saves a compressed version of history as a list of strings.
void MatchHistory::save_history()
{
    QVector<QString> names;
    for ( QString i: history )
        names.push_back(i);

    QSettings settings;
    settings.beginWriteArray("history");
    for ( int i = 0; i < names.size(); i++ ) {
        settings.setArrayIndex(i);
        settings.setValue( "name", history.at(i) );
    }
    settings.endArray();
}
