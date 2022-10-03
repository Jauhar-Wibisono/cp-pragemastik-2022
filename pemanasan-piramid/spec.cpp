#include <tcframe/spec.hpp>
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec
{
protected:
    int N, ans;
    vector<int> A;

    void InputFormat()
    {
        LINE(N);
        LINE(A);
    }

    void OutputFormat()
    {
        LINE(ans);
    }

    void GradingConfig()
    {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints()
    {
        CONS(1 <= N <= 2e5);
        CONS(isValidA(N, A));
    }

private:
    bool isValidA(int n, vector<int> a)
    {
        bool ret = a.size() == n;
        for (int i = 0; i < a.size(); i++)
        {
            ret = ret && (1 <= a[i] && a[i] <= 1e9);
        }
        return ret;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
    void SampleTestCase1()
    {
        Input({"4",
               "1 2 3 4"});
        Output({"55"});
    }

    void TestCases()
    {
        for (int i = 0; i < 5; i++)
        {
            CASE(N = rnd.nextInt(1, 2e3), A = generateA(N, 1e9));
        }
        for (int i = 0; i < 10; i++)
        {
            CASE(N = rnd.nextInt(2e3, 2e5), A = generateA(N, 1e9));
        }
    }

private:
    vector<int> generateA(int n, int mx)
    {
        vector<int> ret;
        while (n--)
        {
            ret.push_back(rnd.nextInt(1, mx));
        }
        return ret;
    }
};