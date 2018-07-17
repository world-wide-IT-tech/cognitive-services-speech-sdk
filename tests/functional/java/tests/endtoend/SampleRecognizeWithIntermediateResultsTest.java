package tests.endtoend;
//
//Copyright (c) Microsoft. All rights reserved.
//Licensed under the MIT license. See LICENSE.md file in the project root for full license information.
//

import static org.junit.Assert.*;

import org.junit.BeforeClass;
import org.junit.Test;
import org.junit.Ignore;

import tests.Settings;
import tests.endtoend.SampleRecognizeWithIntermediateResults;

public class SampleRecognizeWithIntermediateResultsTest {
    SampleRecognizeWithIntermediateResults test;
    
    @BeforeClass
    static public void setUpBeforeClass() throws Exception {
        // Override inputs, if necessary
        Settings.LoadSettings();
    }


    @Ignore("TODO why is the event arg null")
    @Test
    public void test() {
        test = new SampleRecognizeWithIntermediateResults();
        
        test.run();
       
        assertNotNull(test.getSpeechRecognitionResultEventArgs()); // there was at least on intermediate result
        assertNotNull(test.getResult()); // we got the final result
        assertEquals("What's the weather like?", test.getResult().getText()); // we get the text expected
    }
}
