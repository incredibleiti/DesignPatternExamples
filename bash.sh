#!/bin/bash

# --- CONFIGURATION ---
# Define your date range (YYYY-MM-DD)
START_DATE="2026-03-25"
END_DATE="2026-04-01"

# File to modify and commit
FILE="backdated.txt"

# Commit message prefix
MSG_PREFIX="Work on project"

# --- INITIAL SETUP ---
# NOTE: The date command flags (-j -f) are specific to macOS/BSD. 
# For Linux (GNU date), you would use: 
# CURRENT_DATE=$(date -d "$START_DATE" +%s)
# END_DATE_SEC=$(date -d "$END_DATE" +%s)

CURRENT_DATE=$(date -j -f "%Y-%m-%d" "$START_DATE" +%s)
END_DATE_SEC=$(date -j -f "%Y-%m-%d" "$END_DATE" +%s)

ONE_DAY=86400 # Seconds in a day

echo "Starting backdating from $START_DATE to $END_DATE..."

# --- MAIN LOOP ---
while [ "$CURRENT_DATE" -le "$END_DATE_SEC" ]; do
    
    # 1. Get Date String and Day Number (0=Sun, 6=Sat)
    DATE_STR=$(date -j -f "%s" "$CURRENT_DATE" +%Y-%m-%d)
    DAY_NUM=$(date -j -f "%s" "$CURRENT_DATE" +%w)

    # 2. Skip Weekends
    if [ "$DAY_NUM" -eq 0 ] || [ "$DAY_NUM" -eq 6 ]; then
        echo "Skipping weekend day: $DATE_STR"
    else
        # --- 3. Determine Random Commit Count (Weighted for Natural Look) ---
        
        # Generate a random number between 0 and 99
        RANDOM_CHANCE=$(( $RANDOM % 100 ))
        NUM_COMMITS=1 # Baseline is 1 commit

        if [ $RANDOM_CHANCE -ge 90 ]; then
            # 10% chance for a big spike (4 to 6 commits total)
            NUM_COMMITS=$(( $RANDOM % 3 + 4 )) 
        elif [ $RANDOM_CHANCE -ge 70 ]; then
            # 20% chance for a busy day (3 commits total)
            NUM_COMMITS=3
        elif [ $RANDOM_CHANCE -ge 40 ]; then
            # 30% chance for a normal day (2 commits total)
            NUM_COMMITS=2
        fi
        
        echo "--> Committing $NUM_COMMITS times for $DATE_STR"

        # --- 4. Inner Loop for Commit Generation ---
        for i in $(seq 1 $NUM_COMMITS); do
            
            # --- Generate Random Commit Time (9 AM to 5 PM) ---
            # Random Hour (9 to 17)
            RANDOM_HOUR=$(( $RANDOM % 9 + 9 )) 
            # Random Minute (0 to 59)
            RANDOM_MINUTE=$(( $RANDOM % 60 ))
            # Random Second (0 to 59)
            RANDOM_SECOND=$(( $RANDOM % 60 ))
            
            # Format the time string (e.g., 09:35:12)
            TIME_STR=$(printf "%02d:%02d:%02d" $RANDOM_HOUR $RANDOM_MINUTE $RANDOM_SECOND)
            
            # Set the environment variables with the randomized time
            export GIT_AUTHOR_DATE="$DATE_STR $TIME_STR"
            export GIT_COMMITTER_DATE="$DATE_STR $TIME_STR"

            # Ensure file change (Append content to the file)
            echo "Commit #$i on $DATE_STR at $TIME_STR" >> "$FILE"

            # Git commands
            git add "$FILE"
            git commit -m "$MSG_PREFIX on $DATE_STR ($i/$NUM_COMMITS)"
        done
        
    fi

    # Go to next day (Add 1 day in seconds to the timestamp)
    CURRENT_DATE=$((CURRENT_DATE + ONE_DAY))
done

echo "--- Done! All commits created locally. ---"
echo "Next step: Run 'git push --force' to update your remote repository."