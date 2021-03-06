package com.example.backstage.Controller.CatalogueController;

import com.alibaba.fastjson.JSONObject;
import com.example.backstage.Entity.CatalogueEntity.Temporary;
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
* EntryController Tester. 
* 
* @author 罗驰
* @since <pre>6月 22, 2020</pre>
* @version 1.0 
*/
@RunWith(SpringRunner.class)
@SpringBootTest
@AutoConfigureMockMvc
public class EntryControllerTest {
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
* Method: queryDonation(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testQueryDonation() throws Exception { 
//TODO: Test goes here...
    String str="{\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/catalogue/queryDonation")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: addBook(@RequestBody Book book) 
* 
*/ 
@Test
public void testAddBook() throws Exception { 
//TODO: Test goes here...
    Book book=new Book("1234567896412","afeb",1,"jack",true,"华电出版社","2017-02-03",20,"");
    String json= JSONObject.toJSONString(book);
    mvc.perform(MockMvcRequestBuilders.post("/catalogue/addBook")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
}

/** 
* 
* Method: addTemporary(@RequestBody Temporary temporary) 
* 
*/ 
@Test
public void testAddTemporary() throws Exception { 
//TODO: Test goes here...
    Temporary temporary=new Temporary("1234567891234","1213",false,"采访");
    String json= JSONObject.toJSONString(temporary);
    mvc.perform(MockMvcRequestBuilders.post("/catalogue/addTemporary")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(json)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 

/** 
* 
* Method: queryTemporary(@RequestBody JSONObject object) 
* 
*/ 
@Test
public void testQueryTemporary() throws Exception { 
//TODO: Test goes here...
    String str="{\"name\":\"\",\"page\":0,\"size\":10}";
    mvc.perform(MockMvcRequestBuilders.post("/catalogue/queryTemporary")
            .contentType(MediaType.APPLICATION_JSON_UTF8)
            .content(str)
    ).andExpect(MockMvcResultMatchers.status().isOk())
            .andDo(MockMvcResultHandlers.print())
            .andReturn();
} 


} 
