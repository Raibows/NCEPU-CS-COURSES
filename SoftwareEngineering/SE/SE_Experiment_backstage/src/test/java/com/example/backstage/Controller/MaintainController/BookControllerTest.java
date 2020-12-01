package com.example.backstage.Controller.MaintainController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.MaintainEntity.Book;
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
* BookController Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class BookControllerTest {
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
* Method: queryAllBook(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testQueryAllBook() throws Exception { 
//TODO: Test goes here...
    String str="{\"name\":\"\",\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/maintain/queryAllBook")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: updateBook(@RequestBody Book book) 
* 
*/ 
@Test
public void testUpdateBook() throws Exception { 
//TODO: Test goes here...
    Book book=new Book("1234567890123","yes!ok",1,"jack",true,"华电出版社","2017-02-03",20,"");
    String json= JSONObject.toJSONString(book);
    mvc.perform(MockMvcRequestBuilders.post("/maintain/updateBook")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
