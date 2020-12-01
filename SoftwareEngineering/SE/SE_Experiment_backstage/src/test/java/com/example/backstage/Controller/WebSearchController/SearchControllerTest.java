package com.example.backstage.Controller.WebSearchController;

import org.junit.Test; 
import org.junit.Before; 
import org.junit.After; 
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.web.servlet.AutoConfigureMockMvc;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.http.MediaType;
import org.springframework.test.context.junit4.SpringRunner;
import org.springframework.test.context.web.WebAppConfiguration;
import org.springframework.test.web.servlet.MockMvc;
import org.springframework.test.web.servlet.request.MockMvcRequestBuilders;
import org.springframework.test.web.servlet.result.MockMvcResultHandlers;
import org.springframework.test.web.servlet.result.MockMvcResultMatchers;

/** 
* SearchController Tester. 
* 
* @author 罗驰
* @since <pre>6月 24, 2020</pre>
* @version 1.0 
*/
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class SearchControllerTest {
    @Autowired
    private MockMvc mvc;

@Before
public void before() throws Exception { 
} 

@After
public void after() throws Exception { 
} 

/** 
* 
* Method: queryBook(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testQueryBook() throws Exception { 
//TODO: Test goes here...
    String str="{\"all\":\"\",\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/search/queryAllBook")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
