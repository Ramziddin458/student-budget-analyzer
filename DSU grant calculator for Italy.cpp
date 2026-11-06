#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// ISEE (Indicatore della Situazione Economica Equivalente) hisoblash klassi
class IseeCalculator {
private:
    double totalIncome;
    double totalAssets;
    int familyMembers;

    // Italiya DSU standarti bo'yicha oila a'zolari ekvivalent shkalasi
    double getEquivalenceScale() const {
        switch (familyMembers) {
            case 1: return 1.00;
            case 2: return 1.57;
            case 3: return 2.04;
            case 4: return 2.46;
            case 5: return 2.85;
            default: return 2.85 + (0.35 * (familyMembers - 5)); // 5 kishidan ortiq bo'lsa
        }
    }

public:
    IseeCalculator(double income, double assets, int members) {
        totalIncome = income;
        totalAssets = assets;
        familyMembers = members > 0 ? members : 1;
    }

    void calculateAndDisplayEligibility() const {
        double scale = getEquivalenceScale();
        
        // ISE (Situazione Economica) = Daromad + Mol-mulkning 20%
        double ise = totalIncome + (0.20 * totalAssets);
        
        // ISEE va ISPE hisoblash
        double isee = ise / scale;
        double ispe = totalAssets / scale;

        // 2024-2025 yillar uchun taxminiy DSU limitlari (masalan, DiSCo Lazio)
        const double ISEE_LIMIT = 26306.25;
        const double ISPE_LIMIT = 57187.53;

        cout << "\n=========================================\n";
        cout << "       DSU / ISEE PARIFICATO HISOBOTI      \n";
        cout << "=========================================\n";
        cout << fixed << setprecision(2);
        cout << "Oila a'zolari soni     : " << familyMembers << " kishi\n";
        cout << "Ekvivalent shkalasi    : " << scale << "\n";
        cout << "Umumiy daromad (EUR)   : " << totalIncome << " \xE2\x82\xAC\n";
        cout << "Mol-mulk qiymati (EUR) : " << totalAssets << " \xE2\x82\xAC\n";
        cout << "-----------------------------------------\n";
        cout << "Sizning ISEE ko'rsatkichi : " << isee << " \xE2\x82\xAC\n";
        cout << "Sizning ISPE ko'rsatkichi : " << ispe << " \xE2\x82\xAC\n";
        cout << "-----------------------------------------\n";

        // Grantga layoqatlilikni tekshirish
        bool isEligible = (isee <= ISEE_LIMIT) && (ispe <= ISPE_LIMIT);
        
        if (isEligible) {
            cout << "[NATIJA]: TABRIKLAYMIZ! Siz DSU grantiga (100% kontrakt to'lovi va stipendiya) topshirish uchun talablarga javob berasiz.\n";
        } else {
            cout << "[NATIJA]: DIQQAT! Sizning ko'rsatkichlaringiz DSU limitidan oshib ketdi.\n";
            if (isee > ISEE_LIMIT) cout << "- ISEE limiti (" << ISEE_LIMIT << " EUR) dan yuqori.\n";
            if (ispe > ISPE_LIMIT) cout << "- ISPE limiti (" << ISPE_LIMIT << " EUR) dan yuqori.\n";
        }
        cout << "=========================================\n";
    }
};

int main() {
    double income, assets;
    int members;

    cout << "=== DSU Grant Kalkulyatoriga Xush Kelibsiz ===\n";
    
    cout << "1. Oilaning yillik umumiy daromadini kiriting (EUR): ";
    while (!(cin >> income) || income < 0) {
        cout << "Xato! Iltimos, musbat raqam kiriting: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "2. Oilaning jami mol-mulki va bankdagi mablag'ini kiriting (EUR): ";
    while (!(cin >> assets) || assets < 0) {
        cout << "Xato! Iltimos, musbat raqam kiriting: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "3. Oila a'zolari sonini kiriting: ";
    while (!(cin >> members) || members <= 0) {
        cout << "Xato! Oila a'zolari soni 1 yoki undan katta bo'lishi kerak: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    IseeCalculator calculator(income, assets, members);
    calculator.calculateAndDisplayEligibility();

    return 0;
}