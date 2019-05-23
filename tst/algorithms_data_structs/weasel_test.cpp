#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/algorithms_data_structs/weasel_program.h"

namespace {
    using namespace testing;
    using cppchallenge::algorithms_data_structs::Weasel;
    using cppchallenge::algorithms_data_structs::WeaselPhrase;
    class WeaselPhraseTest : public Test {
    protected:
        void SetUp() override {
            std::default_random_engine rd;
            auto seed_data = std::array<int, std::mt19937::state_size>{};
            std::generate(seed_data.begin(), seed_data.end(), std::ref(rd));
            std::seed_seq seq(seed_data.begin(), seed_data.end());

            engine = std::make_shared<std::mt19937>(seq);
        }

        std::shared_ptr<std::mt19937> engine;
    };

    TEST_F(WeaselPhraseTest, ShouldCreateRandomPhrase) {
        auto phrase = WeaselPhrase(engine, 6);
        ASSERT_EQ(phrase.get_phrase().length(), 6);
    }

    TEST_F(WeaselPhraseTest, ShouldCreateRandomPhraseFromString) {
       auto phrase = WeaselPhrase(engine, "test") ;
       ASSERT_EQ(phrase.get_phrase().length(), 4);
       ASSERT_EQ(phrase.get_phrase(), "test");
    }

    TEST_F(WeaselPhraseTest, ReplicationNoMutationChance) {
        auto phrase = WeaselPhrase(engine, "test");

        auto result = phrase.replicate(.0);
        ASSERT_EQ(phrase.get_phrase(), result.get_phrase());
    }

    TEST_F(WeaselPhraseTest, ReplicationAlwaysMutate) {
        auto phrase = WeaselPhrase(engine, "test");
        auto result = phrase.replicate(1.0);
        ASSERT_NE(phrase.get_phrase(), result.get_phrase());
    }

    TEST_F(WeaselPhraseTest, IsSame) {
        auto phrase = WeaselPhrase(engine, "test");
        ASSERT_TRUE(phrase.is_same("test"));
        ASSERT_FALSE(phrase.is_same("tEst"));
    }

    TEST_F(WeaselPhraseTest, Score) {
        auto phrase = WeaselPhrase(engine, "test");
        ASSERT_EQ(phrase.score("test"), 4);
        ASSERT_EQ(phrase.score("tist"), 3);
        ASSERT_EQ(phrase.score("aula"), 0);
    }

    TEST(WeaselSimulationTest, ShouldFindThePhrase) {
        auto simulation = Weasel{};
        auto result = simulation.simulate("METHINKS IT IS LIKE A WEASEL", 0.05);
        ASSERT_GT(result, 1);
    }
}
