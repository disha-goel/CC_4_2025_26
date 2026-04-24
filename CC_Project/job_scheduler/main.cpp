#include <iostream>
#include <iomanip>
#include <limits>
#include "scheduler.h"

void sep(char c = '-', int n = 52) { std::cout << std::string(n, c) << '\n'; }

void printJobTable(const std::vector<Job>& jobs) {
    if (jobs.empty()) { std::cout << "  (empty)\n"; return; }
    std::cout << "  " << std::left
              << std::setw(5)  << "ID"
              << std::setw(18) << "Name"
              << std::setw(11) << "Deadline"
              << "Profit\n";
    sep('-', 46);
    for (const auto& j : jobs)
        std::cout << "  " << std::left
                  << std::setw(5)  << j.id
                  << std::setw(18) << j.name
                  << std::setw(11) << j.deadline
                  << j.profit << '\n';
}

int main() {
    JobScheduler scheduler;
    int nextId = 1;

    sep('=');
    std::cout << "  Job Scheduling System  |  Greedy Algorithm  |  DAA\n";
    sep('=');

    int choice = -1;
    while (choice != 0) {
        std::cout << "\n  1. Add Job\n"
                  << "  2. Remove Job\n"
                  << "  3. View Jobs\n"
                  << "  4. Run Scheduler\n"
                  << "  5. Load Sample Data\n"
                  << "  6. Clear All\n"
                  << "  0. Exit\n";
        sep();
        std::cout << "  Choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name; int deadline, profit;
            std::cout << "  Name     : ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, name);
            if (name.empty()) name = "Job-" + std::to_string(nextId);
            std::cout << "  Deadline : "; std::cin >> deadline;
            std::cout << "  Profit   : "; std::cin >> profit;
            try {
                scheduler.addJob(nextId, name, deadline, profit);
                std::cout << "  Added \"" << name << "\" (ID " << nextId << ")\n";
                ++nextId;
            } catch (const std::exception& e) {
                std::cout << "  Error: " << e.what() << '\n';
            }

        } else if (choice == 2) {
            int id; std::cout << "  Job ID to remove: "; std::cin >> id;
            std::cout << (scheduler.removeJob(id) ? "  Removed.\n" : "  ID not found.\n");

        } else if (choice == 3) {
            sep();
            std::cout << "  JOB POOL\n"; sep();
            printJobTable(scheduler.getJobs());

        } else if (choice == 4) {
            if (scheduler.getJobs().empty()) { std::cout << "  No jobs to schedule.\n"; continue; }
            ScheduleResult res = scheduler.schedule();
            sep('=');
            std::cout << "  SCHEDULE RESULT\n"; sep('=');
            std::cout << "  " << std::left
                      << std::setw(6)  << "Slot"
                      << std::setw(5)  << "ID"
                      << std::setw(18) << "Name"
                      << std::setw(11) << "Deadline"
                      << "Profit\n";
            sep('-', 50);
            for (int i = 0; i < (int)res.scheduledJobs.size(); ++i) {
                const auto& j = res.scheduledJobs[i];
                std::cout << "  " << std::left
                          << std::setw(6)  << res.timeSlots[i]
                          << std::setw(5)  << j.id
                          << std::setw(18) << j.name
                          << std::setw(11) << j.deadline
                          << j.profit << '\n';
            }
            sep();
            if (!res.skippedJobs.empty()) {
                std::cout << "  Skipped jobs:\n";
                for (const auto& j : res.skippedJobs)
                    std::cout << "    - " << j.name << " (profit " << j.profit << ")\n";
                sep();
            }
            std::cout << "  Scheduled : " << res.scheduledJobs.size()
                      << " / " << scheduler.getJobs().size() << " jobs\n";
            std::cout << "  Total Profit : " << res.totalProfit << '\n';
            sep('=');

        } else if (choice == 5) {
            scheduler.clear(); nextId = 1;
            scheduler.addJob(nextId++, "Task-A", 2, 100);
            scheduler.addJob(nextId++, "Task-B", 1, 19);
            scheduler.addJob(nextId++, "Task-C", 2, 27);
            scheduler.addJob(nextId++, "Task-D", 1, 25);
            scheduler.addJob(nextId++, "Task-E", 3, 15);
            scheduler.addJob(nextId++, "Task-F", 3, 50);
            scheduler.addJob(nextId++, "Task-G", 2, 60);
            std::cout << "  Loaded 7 sample jobs.\n";

        } else if (choice == 6) {
            scheduler.clear(); nextId = 1;
            std::cout << "  Cleared.\n";

        } else if (choice != 0) {
            std::cout << "  Invalid option.\n";
        }
    }

    std::cout << "  Goodbye.\n";
    return 0;
}
