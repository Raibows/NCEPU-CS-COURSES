<template>
  <div>
    <el-row style="margin-top: 40px;">
      <el-col :span="6" :offset="8">
        <el-input v-model="keyword" placeholder="请输入查询内容（支持模糊搜索）" class="input-with-select">
          <el-button slot="append" icon="el-icon-search" @click="queryTemporary" />
        </el-input>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="18" :offset="7" style="margin-top: 20px;">
        <el-table
          :data="tableData"
          border
          style="width: 50%"
        >
          <el-table-column
            fixed
            prop="isbn"
            label="ISBN"
            width="150"
          />
          <el-table-column
            prop="bookName"
            label="书名"
            width="120"
          />
          <el-table-column
            prop="opName"
            label="来源"
            width="120"
          />
          <el-table-column
            prop="hasEntry"
            label="是否已录入"
            width="122"
          >
            <template slot-scope="scope">
              <el-tag
                :type="scope.row.hasEntry === true ? 'success' : 'danger'"
                disable-transitions
              >{{ scope.row.hasEntry === true ? '已录入' :'未录入' }}
              </el-tag>
            </template>
          </el-table-column>
        </el-table>
      </el-col>
    </el-row>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="8">
        <el-pagination
          :current-page="currentPage"
          :page-sizes="[5, 10, 20]"
          :page-size="pageSize"
          layout="total, sizes, prev, pager, next, jumper"
          :total="total"
          @size-change="handleSizeChange"
          @current-change="handleCurrentChange"
        />
      </el-col>
    </el-row>
    <reimbursement ref="reimbursement_form" />
  </div>
</template>

<script>
import { queryTemporary } from '../../../api/catalogue'

export default {
  name: 'CatalogueNotification',
  data() {
    return {
      keyword: '',
      type: '',
      currentPage: 1,
      pageSize: 5,
      total: 5,
      tableData: []
    }
  },
  created() {
    this.queryTemporary()
  },
  methods: {
    queryTemporary() {
      queryTemporary({
        name: this.keyword,
        page: this.currentPage - 1,
        size: this.pageSize
      }).then(response => {
        this.tableData = response.data.content
        this.currentPage = response.data.pageable.pageNumber + 1
        this.pageSize = response.data.pageable.pageSize
        this.total = response.data.totalElements
      })
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.queryTemporary()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.queryTemporary()
    }
  }

}
</script>

<style lang="scss" scoped>

</style>
