#ifndef MATCHHISTORY_H
#define MATCHHISTORY_H

#include <QVector>
#include <QString>

class MatchHistory
{
public:
    // Default ctor.
    MatchHistory();

    /**
     * @brief is_match
     * @pre The vector of strings must have each name as a seperate element of the vector.
     * @return If is match
     */
    bool is_match( QVector<QString> top );

    /**
     * @brief set_history
     * @pre Must be a vector of names that are to be used as the final output
     * ( In other words, names must be tested through the is_match function. )
     * @post New string of name histories is written in os.
     */
    void set_history(QVector<QString> top);

    /**
     * @brief adjust_matches
     * @param to_remove
     * @pre Needs a vector of names.
     * @post Internal history list will no longer contain the names in precondition.
     */
    void adjust_matches(QVector<QString> to_remove);

private:
    QVector<QString> get_history();
    void save_history();

    QVector<QString> history;
    QVector<QString> curr_top;
};

#endif // MATCHHISTORY_H
