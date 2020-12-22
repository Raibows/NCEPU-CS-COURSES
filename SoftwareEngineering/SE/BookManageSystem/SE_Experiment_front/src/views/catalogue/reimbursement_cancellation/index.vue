<template>
  <div>
    <el-row style="margin-top: 20px;">
      <el-col :span="12" :offset="6">
        <el-input v-model="keyword" placeholder="请输入查询内容（支持模糊搜索）" class="input-with-select">
          <el-button slot="append" icon="el-icon-search" @click="searchDamage" />
        </el-input>
      </el-col>
      <el-col :span="2" :offset="1">
        <el-button type="primary" round @click="openAddForm({})">添加待报损图书</el-button>
      </el-col>
    </el-row>
    <el-row>
      <el-col :span="18" :offset="4" style="margin-top: 20px;">
        <el-table
          :data="tableData"
          border
          style="width: 90%"
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
            show-overflow-tooltip
            prop="reason"
            label="报损原因"
            width="180"
          />
          <el-table-column
            prop="price"
            label="书籍价格"
            width="120"
          />
          <el-table-column
            prop="state"
            label="审批状态"
            width="70"
          >
            <template slot-scope="scope">
              <el-tag
                :type="scope.row.state === true ? 'success' : 'danger'"
                disable-transitions
              >{{ scope.row.state === true ? '通过' :'未通过' }}
              </el-tag>
            </template>
          </el-table-column>
          <el-table-column
            prop="checker"
            label="审批人"
            width="100"
          />
          <el-table-column
            fixed="right"
            label="操作"
            width="180"
          >
            <template slot-scope="scope">
              <el-button type="primary" size="small" @click="open_book_form(scope.row)">编辑</el-button>
              <el-button type="danger" size="small" @click="deleteDamage(scope.row)">注销</el-button>
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

import Reimbursement from './components/Reimbursement'
import { queryDamgage, deleteDamage } from '../../../api/catalogue'

export default {
  name: 'CatalogueReimbursementCancellation',
  components: { Reimbursement },
  data() {
    return {
      keyword: '',
      currentPage: 1,
      pageSize: 10,
      total: 10,
      tableData: []
    }
  },
  created() {
    this.searchDamage()
  },
  methods: {
    open_book_form(row) {
      if (row.state === true) {
        row.state = '通过'
      } else {
        row.state = '未通过'
      }
      this.$refs['reimbursement_form'].visible = true
      this.$refs['reimbursement_form'].reimbursement = row
      this.$refs['reimbursement_form'].isAdd = false
    },
    openAddForm(row) {
      this.$refs['reimbursement_form'].visible = true
      this.$refs['reimbursement_form'].reimbursement = row
      this.$refs['reimbursement_form'].isAdd = true
    },
    searchDamage() {
      queryDamgage({ name: this.keyword, page: this.currentPage - 1, size: this.pageSize }).then(response => {
        console.log(response.data.content)
        this.tableData = response.data.content
        this.currentPage = response.data.pageable.pageNumber + 1
        this.pageSize = response.data.pageable.pageSize
        this.total = response.data.totalElements
      })
    },
    handleSizeChange(val) {
      this.pageSize = val
      this.searchDamage()
    },
    handleCurrentChange(val) {
      this.currentPage = val
      this.searchDamage()
    },
    deleteDamage(row) {
      this.$confirm('此操作将删除该图书, 是否继续?', '提示', {
        confirmButtonText: '确定',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        if (row.state === false) {
          this.$message.error('审核未通过!')
        } else {
          deleteDamage({ isbn: row.isbn }).then(response => {
            this.searchDamage()
            this.$message({
              type: 'success',
              message: response.msg
            })
          })
        }
      }).catch(() => {
        this.$message({
          type: 'info',
          message: '已取消删除'
        })
      })
    }
  }
}
</script>

<style lang="scss" scoped>

</style>
