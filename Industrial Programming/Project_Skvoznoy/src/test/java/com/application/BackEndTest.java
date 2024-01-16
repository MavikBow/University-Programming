package com.application;

import org.junit.jupiter.api.Nested;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class BackEndTest
{
    @Nested
    class Correct
    {
        @Test
        void testValidFlags1()
        {
            String[]flags = new String[]{"-z", "-d"};
            assertTrue(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags2()
        {
            String[]flags = new String[]{"-d", "-z"};
            assertTrue(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags3()
        {
            String[]flags = new String[]{"-j", "-e"};
            assertTrue(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags4()
        {
            String[]flags = new String[]{"-uz", "-e"};
            assertTrue(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags5()
        {
            String[]flags = new String[]{"-d"};
            assertTrue(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags6()
        {
            String[]flags = new String[]{"-uj"};
            assertTrue(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags7()
        {
            String[]flags = new String[]{"-z", "-e"};
            assertTrue(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags8()
        {
            String[]flags = new String[]{""};
            assertTrue(BackEnd.validFlags(flags));
        }
    }

    @Nested
    class Incorrect
    {
        @Test
        void testValidFlags1()
        {
            String[]flags = new String[]{"-r", "-d"};
            assertFalse(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags2()
        {
            String[]flags = new String[]{"-d", "-o"};
            assertFalse(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags3()
        {
            String[]flags = new String[]{"your", "mom"};
            assertFalse(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags4()
        {
            String[]flags = new String[]{"uz", "-e"};
            assertFalse(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags5()
        {
            String[]flags = new String[]{"d"};
            assertFalse(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags6()
        {
            String[]flags = new String[]{"-ju"};
            assertFalse(BackEnd.validFlags(flags));
        }

        @Test
        void testValidFlags7()
        {
            String[]flags = new String[]{"-z", "-j"};
            assertFalse(BackEnd.validFlags(flags));

        }
        @Test
        void testValidFlags8()
        {
            String[]flags = new String[]{"java"};
            assertFalse(BackEnd.validFlags(flags));
        }
        @Test
        void testValidFlags9()
        {
            String[]flags = new String[]{"never", "gonna", "give", "you", "up"};
            assertFalse(BackEnd.validFlags(flags));
        }
    }
}
